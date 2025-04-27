/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:54:25 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:30:27 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_init(t_data *data)
{
	data->player.w = 0;
	data->player.s = 0;
	data->player.a = 0;
	data->player.d = 0;
	data->player.left = 0;
	data->player.right = 0;
}

void	player_init(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			if (data->map->cub_map[i][j] == 'N' ||
				data->map->cub_map[i][j] == 'S' ||
				data->map->cub_map[i][j] == 'E' ||
				data->map->cub_map[i][j] == 'W')
			{
				data->player.pos_x = (double)j + 0.5;
				data->player.pos_y = (double)i + 0.5;
				player_vector(&data->player, data->map->cub_map[i][j]);
				camera_plane(&data->player, data->map->cub_map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
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
	map->flage = 0;
	map->cub_map = NULL;
}
