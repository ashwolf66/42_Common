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
	map_init(&(data->map));
	player_init(&(data->player));
}

void	player_init(t_player *player)
{
	player->px = (float)WIN_WIDTH / 2.0f;
	player->py = (float)WIN_HEIGHT / 2.0f;
	player->angle = (float)M_PI / 2.0f;
}

void    draw_square(t_data *data, int x, int y, int color)
{
    int i, j;

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            char *dst = data->img.addr + ((y + i) \
			* data->img.line_length + (x + j) * (data->img.bit_per_pixel / 8));
            *(unsigned int*)dst = color;
        }
    }
}