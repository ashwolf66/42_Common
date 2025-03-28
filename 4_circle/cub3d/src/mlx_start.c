/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:54:11 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:30:54 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mlx_start(t_data *data, t_map *map)
{
	data->map = map;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit(1);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (data->win == NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (data->img.img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bit_per_pixel,
			&data->img.line_length, &data->img.endian);
	if (texture_set(data))
		exit(1);
	return (0);
}

void	player_vector(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

void	camera_plane(t_player *player, char direction)
{
	if (direction == 'N' || direction == 'S')
	{
		if (direction == 'N')
			player->pla_x = 0.66;
		else if (direction == 'S')
			player->pla_x = -0.66;
		player->pla_y = 0;
	}
	else if (direction == 'E' || direction == 'W')
	{
		player->pla_x = 0;
		if (direction == 'E')
			player->pla_y = 0.66;
		else if (direction == 'W')
			player->pla_y = -0.66;
	}
}
