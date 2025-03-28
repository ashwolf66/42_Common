/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:30:36 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:35:04 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (operation_line(line, size, lines, map))
		{
			free(line);
			free_double(*lines);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!(*lines))
		return (1);
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
