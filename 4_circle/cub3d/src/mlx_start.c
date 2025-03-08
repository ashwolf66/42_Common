/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:54:11 by jacha             #+#    #+#             */
/*   Updated: 2025/01/18 16:54:13 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_start(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (data->win == NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (data->img.img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, \
	&data->img.bit_per_pixel, &data->img.line_length, &data->img.endian);
	map_init(data);
	player_init(data);
}

void player_init(t_data *data)
{
	for (int y = 0; y < data->map.height; y++)
	{
		for (int x = 0; x < data->map.width; x++)
		{
			if (data->map.cub_map[y][x] == 'N' ||
				data->map.cub_map[y][x] == 'S' ||
				data->map.cub_map[y][x] == 'E' ||
				data->map.cub_map[y][x] == 'W')
			{
				data->player.pos_x = x * TILE_SIZE + TILE_SIZE / 2;
				data->player.pos_y = y * TILE_SIZE + TILE_SIZE / 2;

				// 방향 설정
				if (data->map.cub_map[y][x] == 'N')
				{
					data->player.dir_x = 0;
					data->player.dir_y = -1;
					data->player.pla_x = 0.66;
					data->player.pla_y = 0;
				}
				else if (data->map.cub_map[y][x] == 'S')
				{
					data->player.dir_x = 0;
					data->player.dir_y = 1;
					data->player.pla_x = -0.66;
					data->player.pla_y = 0;
				}
				else if (data->map.cub_map[y][x] == 'E')
				{
					data->player.dir_x = 1;
					data->player.dir_y = 0;
					data->player.pla_x = 0;
					data->player.pla_y = 0.66;
				}
				else if (data->map.cub_map[y][x] == 'W')
				{
					data->player.dir_x = -1;
					data->player.dir_y = 0;
					data->player.pla_x = 0;
					data->player.pla_y = -0.66;
				}
			}
		}
	}
	data->player.w = 0;
	data->player.s = 0;
	data->player.a = 0;
	data->player.d = 0;
	data->player.left = 0;
	data->player.right = 0;
}

void map_init(t_data *data)
{
    static char *map_data[] = {
		"11111111",
		"10000001",
		"10N00101",
		"10000001",
		"11111111"
    };

    data->map.cub_map = map_data;
    data->map.width = 8;
    data->map.height = 5;
	data->map.floor = 0xFFFFFF;
	data->map.ceiling = 0x00A0A0;
}
