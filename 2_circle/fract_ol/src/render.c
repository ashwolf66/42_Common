/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:35:29 by jacha             #+#    #+#             */
/*   Updated: 2024/07/28 09:36:01 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixel + offset) = color;
}

void	man_jul(t_complex *z, t_complex *c, t_data *data)
{
	if (!ft_strncmp(data->title, "julia", 5))
	{
		c->x = data->julia_x;
		c->y = data->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

void	handle_pixel(int x, int y, t_data *data)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = (map(x, -2, +2, WIDTH) * data->zoom) + data->shift_x;
	z.y = (map(y, +2, -2, HEIGHT) * data->zoom) + data->shift_y;
	man_jul(&z, &c, data);
	while (i < data->iteration)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > data->escape_value)
		{
			color = map(i, BLACK, WHITE, data->iteration);
			my_pixel_put(x, y, &data->img, color);
			return ;
		}
		i++;
	}
	my_pixel_put(x, y, &data->img, NEON_ORANGE);
}

void	data_render(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, data);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img. img, 0, 0);
}
