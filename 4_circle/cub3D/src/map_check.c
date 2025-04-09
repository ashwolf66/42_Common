/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:30:47 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:30:49 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_map_validate(t_map *map)
{
	if (cub_map_validate_check(map))
		return (1);
	if (cub_map_check(map))
		return (1);
	if (player_check(map) != 1)
		return (1);
	return (0);
}

int	cub_map_validate_check(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->cub_map[i][j] != '1' && map->cub_map[i][j] != ' ')
			{
				if (wall_check(i, j, map))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	is_inside_map(int i, int j, t_map *map)
{
	return (i >= 0 && i < map->height && j >= 0 && j < map->width);
}

int	wall_check(int i, int j, t_map *map)
{
	if (!map || !map->cub_map)
		return (1);
	if (i < 0 || i > map->height - 1 || j < 0 || j > map->width - 1)
		return (1);
	if (!is_inside_map(i - 1, j, map) || map->cub_map[i - 1][j] == ' ')
		return (1);
	if (!is_inside_map(i + 1, j, map) || map->cub_map[i + 1][j] == ' ')
		return (1);
	if (!is_inside_map(i, j - 1, map) || map->cub_map[i][j - 1] == ' ')
		return (1);
	if (!is_inside_map(i, j + 1, map) || map->cub_map[i][j + 1] == ' ')
		return (1);
	return (0);
}

int	cub_map_check(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->cub_map[i][j] != '0' && map->cub_map[i][j] != '1' && \
				map->cub_map[i][j] != 'N' && map->cub_map[i][j] != 'S' && \
				map->cub_map[i][j] != 'E' && map->cub_map[i][j] != 'W' && \
				map->cub_map[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
