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

t_map	*init_map(char *map_file)
{
	int		fd;
	t_map	*temp;

	temp = (t_map *)malloc(sizeof(t_map) * 1);
	if (!temp)
	{
		free(temp);
		return (NULL);
	}
	init_texture(temp);
	init_map_av(temp);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		free_map(temp);
		return (NULL);
	}
	if (operation_map_file(temp, fd))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (temp);
}

int	operation_map_file(t_map *map, int fd)
{
	int		map_size;
	char	**map_line;

	map_size = 0;
	map_line = NULL;
	if (read_file(fd, &map_size, &map_line, map))
	{
		free_map(map);
		return (1);
	}
	if (operation_cub_map(&map_line, map))
	{
		free_map(map);
		return (1);
	}
	return (0);
}

int	read_file(int fd, int *size, char ***lines, t_map *map)
{
	char	*line;

	*lines = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (operation_line(line, size, lines, map))
		{
			free(line);
			if (*lines)
				free_double(*lines);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (!(*lines))
		return (1);
	return (0);
}

int	operation_cub_map(char ***lines, t_map *map)
{
	if (parse_cub_map(*lines, map))
	{
		free_double(*lines);
		return (1);
	}
	free_double(*lines);
	return (0);
}
