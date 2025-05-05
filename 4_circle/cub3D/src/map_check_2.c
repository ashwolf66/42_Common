/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:30:43 by jacha             #+#    #+#             */
/*   Updated: 2025/04/22 13:43:25 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_check(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->cub_map[i][j] == 'N' || map->cub_map[i][j] == 'S' || \
map->cub_map[i][j] == 'E' || map->cub_map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
