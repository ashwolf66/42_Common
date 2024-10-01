/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:37:23 by jacha             #+#    #+#             */
/*   Updated: 2024/07/28 09:38:15 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	value_init(t_data *data)
{
	data->escape_value = 4;
	data->iteration = 42;
	data->shift_x = 0.0;
	data->shift_y = 0.0;
	data->zoom = 1.0;
}

void	event_init(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_handler, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_handler, data);
	mlx_hook(data->win, 17, 1L << 17, close_handler, data);
	mlx_hook(data->win, 6, 1L << 6, case_jul, data);
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, data->title);
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
	data->img.pixel = mlx_get_data_addr(data->img.img, &data->img.bpp, \
			&data->img.line_len, &data->img.endian);
	event_init(data);
	value_init(data);
}
