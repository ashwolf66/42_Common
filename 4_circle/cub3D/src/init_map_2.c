/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:30:27 by jacha             #+#    #+#             */
/*   Updated: 2025/04/27 11:03:08 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	operation_line(char *line, int *size, char ***lines, t_map *map)
{
	operation_line_end_space(&line);
	if (ft_strlen(line) != 0 && check_t_c(map))
	{
		if (set_t_c(line, map))
			return (1);
	}
	else if (!check_t_c(map))
	{
		if (map->flage == 2)
			return (1);
		if (map->flage == 1 && ft_strlen(line) == 0)
		{
			map->flage = 2;
			return (0);
		}
		if (ft_strlen(line) != 0 && set_cub_map(line, size, lines))
			return (1);
		map->flage = 1;
	}
	return (0);
}

int	check_t_c(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!map->texture[i].path)
			return (1);
		i++;
	}
	if (map->ceiling.color == -1 || map->floor.color == -1)
		return (1);
	return (0);
}

int	set_t_c(char *line, t_map *map)
{
	operation_line_start_space(&line);
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
	else
		return (1);
	return (0);
}

int	set_cub_map(char *line, int *size, char ***lines)
{
	char	**temp;

	temp = malloc(sizeof(char *) * (*size + 2));
	if (!temp)
	{
		free(line);
		return (1);
	}
	if (*lines)
	{
		ft_memcpy(temp, *lines, sizeof(char *) * (*size));
		free(*lines);
	}
	*lines = temp;
	(*lines)[*size] = ft_strdup(line);
	if (!(*lines)[*size])
	{
		free(line);
		return (1);
	}
	(*lines)[*size + 1] = NULL;
	(*size)++;
	return (0);
}
