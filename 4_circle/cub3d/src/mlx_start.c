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
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (data->win == NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img.img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->img.arr = mlx_get_data_addr(data->img.img, \
	&data->img.bit_per_pixel, &data->img.line_length, &data->img.endian);
	event_init(data);
}
