/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:56:49 by jacha             #+#    #+#             */
/*   Updated: 2025/03/13 13:01:33 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	*map;
	t_data	*data;

	data = NULL;
	if(argv_check(ac, av[1], map, data))
		return (1);
	if (init_map(av[1], map, data))
		return (1);
	mlx_start(&data);
	mlx_loop_hook((*data).mlx, refresh_map, data);
	mlx_loop((*data).mlx);
	return (0);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx)
	{
		if (data->mlx)
			mlx_destroy_window(data->mlx, data->win);
		if (data->img.img)
			mlx_destroy_image(data->mlx, data->img.img);
	}
	free(data);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_texture(map);
	free_cubmap(map);
	free(map);
}

void	free_texture(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < 4)
	{
		if (map->texture[i].path)
		{
			free(map->texture[i].path);
			map->texture[i].path = NULL;
		}
		i++;
	}
}

void	free_cubmap(t_map *map)
{
	int	i;

	if (!map || !map->cub_map)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->cub_map[i])
		{
			free(map->cub_map[i]);
			map->cub_map[i] = NULL;
		}
		i++;
	}
	free(map->cub_map);
	map->cub_map = NULL;
}

int	refresh_map(t_data *data)
{
	event_handle(&data);
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bit_per_pixel,
			&data->img.line_length, &data->img.endian);
	move_funtion(data);
	fill_background(data);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

void	fill_background(t_data *data)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		dst = data->img.addr + y * data->img.line_length;
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < (WIN_HEIGHT / 2))
				*(unsigned int *)(dst + x * (data->img.bit_per_pixel / 8))
					= data->map->ceiling.color;
			else
				*(unsigned int *)(dst + x * (data->img.bit_per_pixel / 8))
					= data->map->floor.color;
			x++;
		}
		y++;
	}
}

int	argv_check(int ac, char *map_file, t_map *map, t_data *data)
{
	if (ac != 2)
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	if (extension_check(map_file, ".cub"))
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	if (file_check(map_file, map, data))
		return (1);
	return (0);
}

int	extension_check(char *map_file, char *cub)
{
	int	file_len;
	int	ext_len;

	file_len = ft_strlen(map_file);
	ext_len = ft_strlen(cub);
	while (file_len > 0)
	{
		if (ext_len == 0)
			break ;
		if (map_file[file_len - 1] != cub[ext_len - 1])
			return (1);
		ext_len--;
		file_len--;
	}
	if (file_len < 1)
		return (1);
	return (0);
}

int	file_check(char *map_file, t_map *map, t_data *data)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	close(fd);
	return (0);
}

int	init_map(char *map_file, t_map *map, t_data *data)
{
	int	fd;

	map = (t_map *)malloc(sizeof(t_map) * 1);
	if (!map)
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	init_texture(map);
	init_map_av(map);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	if (operation_map_file(map_file, map, data, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	init_texture(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		map->texture[i].path = NULL;
		map->texture[i].img.img = NULL;
		map->texture[i].img.addr = NULL;
		map->texture[i].img.bit_per_pixel = 0;
		map->texture[i].img.line_length = 0;
		map->texture[i].img.endian = 0;
		map->texture[i].img.width = 0;
		map->texture[i].img.height = 0;
		i++;
	}
}

void	init_map_av(t_map *map)
{
	map->floor.color = -1;
	map->ceiling.color = -1;
	map->height = -1;
	map->width = -1;
	map->cub_map = NULL;
}

int	operation_map_file(char *map_file, t_map *map, t_data *data, int fd)
{
	int		map_size;
	char	**map_line;

	map_size = 0;
	map_line = NULL;
	if (read_file(fd, &map_size, &map_line, map))
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	if (operation_cub_map(fd, &map_line, map))
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	return (0);
}

int	read_file(int fd, int *size, char ***lines, t_map *map)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		if (operation_line(line, size, lines, map))
		{
			free(line);
			free_double(*lines);
			return (1);
		}
		free(line);
	}
	if (!(*lines))
		return (1);
	return (0);
}

int	operation_line(char *line, int *size, char ***lines, t_map *map)
{
	char	*origin_line;

	operation_line_end_space(&line);
	origin_line = ft_strdup(line);
	operation_line_start_space(&line);
	if (ft_strlen(line) > 0)
	{
		if (check_t_c(map))
		{
			if (set_t_c(line, map))
				return (1);
		}
		else
		{
			if (set_cub_map(origin_line, size, lines, map))
			{
				free(origin_line);
				return (1);
			}
		}
	}
	free(origin_line);
	return (0);
}

int	check_t_c(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->texture[i].path)
			return (0);
		i++;
	}
	if (map->ceiling.color != -1 || map->floor.color != -1)
		return (0);
	return (1);
}

int set_t_c(char *line, t_map *map)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (set_texture(line, map, 0));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (set_texture(line, map, 1));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (set_texture(line, map, 2));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (set_texture(line, map, 3));
	else if (ft_strncmp(line, "F", 1) == 0)
		return (set_color(line, &map->floor, map, 'F'));
	else if (ft_strncmp(line, "C", 1) == 0)
		return (set_color(line, &map->ceiling, map, 'C'));
}

void operation_line_end_space(char **line)
{
    size_t len;

    len = strlen(*line);
    while (len > 0 && ((*line)[len - 1] == '\n' \
	|| (*line)[len - 1] == '\t' || (*line)[len - 1] == ' '))
    {
        (*line)[len - 1] = '\0';
        len--;
    }
}

void operation_line_start_space(char **line)
{
    while (**line && (**line == ' ' || **line == '\t'))
        (*line)++;
}

void operation_line_space_color(char **line)
{
    char	*src;
	char	*dst;
    
	*src = *line;
	*dst = *line;
    while (*src)
    {
        if (*src != ' ' && *src != '\t' && *src != '\n')
        {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int	set_texture(char *line, t_map *map, int direct)
{
	char	**temp;

	if (map->texture[direct].path)
		return (1);
	(*line) += 2;
	operation_line_start_space(&line);
	temp = ft_split(line, ' ');
	if (!temp || !temp[0] || temp[1])
	{
		free_double(temp);
		return (1);
	}
	map->texture[direct].path = ft_strdup(temp[0]);
	free_double(temp);
	if (!map->texture[direct].path)
		return (1);
	return (0);
}
int	set_color(char *line, t_color *color, t_map *map, char chr)
{
	char	**temp;

	if ((chr == 'F' && map->floor.color != -1) || \
	(chr == 'C' && map->ceiling.color != -1))
		return (1);
	(*line) += 1;
	operation_line_space_color(&line);
	temp = ft_split(line, ',');
	if (!temp || !temp[0] || !temp[1] || !temp[2] || temp[3])
	{
		free_double(temp);
		return (1);
	}
	if (alloc_color(temp, color, map))
		return (1);
	return (0);
}

void	free_double(char **temp)
{
	int	i;

	if (!temp || !*temp)
		return ;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
	free(temp);
	temp = NULL;
}

int	alloc_color(char **colors, t_color *color, t_map *map)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_double(colors);
		return (1);
	}
	color->color = (r << 16) | (g << 8) | b;
	free_double(colors);
	return (0);
}

int	set_cub_map(char *line, int *size, char ***lines, t_map *map)
{
	char	**temp;

	temp = malloc(sizeof(char *) * (*size + 2));
	if (!temp)
		return (1);
	if (*lines)
	{
		ft_memcpy(temp, *lines, sizeof(char *) * (*size));
		free(*lines);
	}
	*lines = temp;
	(*lines)[*size] = ft_strdup(line);
	if (!(*lines)[*size])
		return (1);
	(*lines)[*size + 1] = NULL;
	(*size)++;
	return (0);
}

int	operation_cub_map(int fd, char ***lines, t_map *map)
{
	if (parse_cub_map(*lines, map))
	{
		free_double(*lines);
		return (1);
	}
	free_double(*lines);
	return (0);
}

int	parse_cub_map(char **lines, t_map *map)
{
	if (!lines || !map)
		return (1);
	map->height = check_map_height(lines);
	if (map->height < 3)
		return (1);
	map->width = check_map_width(lines);
	if (map->width < 3)
		return (1);
	map->cub_map = create_cub_map(lines, map);
	if (!map->cub_map)
		return (1);
	if (cub_map_validate(map))
		return (1);
}

int	check_map_height(char **lines)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 0)
			count++;
		i++;
	}
	return (count);
}

int	check_map_width(char **lines)
{
	int	max;
	int	temp;
	int	i;

	max = 0;
	i = 0;
	while (lines[i])
	{
		temp = ft_strlen(lines[i]);
		if (max <= temp)
			max = temp;
		i++;
	}
	return (max);
}

char	**create_cub_map(char **lines, t_map *map)
{
	char	**temp;
	int	i;
	int	j;

	temp = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		if (init_row(temp, i, map))
			return (NULL);
		j = 0;
		while (lines[i][j] && j < map->width)
		{
			temp[i][j] = lines[i][j];
			j++;
		}
		i++;
	}
	temp[map->height] = NULL;
	return (temp);
}

int	init_row(char **temp, int i, t_map *map)
{
	temp[i] = (char *)malloc(sizeof(char) * (map->width + 1));
	if (!temp[i])
	{
		free_double(temp);
		return (1);
	}
	ft_memset(temp[i], ' ', map->width);
	temp[i][map->width] = '\0';
	return (0);
}

int	cub_map_validate(t_map *map)
{
	
}