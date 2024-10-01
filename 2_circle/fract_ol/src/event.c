/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:36:31 by jacha             #+#    #+#             */
/*   Updated: 2024/07/28 09:36:33 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_handler(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_data *data)
{
	if (keysym == 65307)
		close_handler(data);
	else if (keysym == 65361)
		data->shift_x += 0.5;
	else if (keysym == 65363)
		data->shift_x -= 0.5;
	else if (keysym == 65362)
		data->shift_y -= 0.5;
	else if (keysym == 65364)
		data->shift_y += 0.5;
	else if (keysym == 65451)
		data->iteration += 10;
	else if (keysym == 65453)
		data->iteration -= 10;
	data_render(data);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_data *data)
{
	if (x == -999 && y == -999)
		return (0);
	if (button == 5)
		data->zoom *= 0.95;
	else if (button == 4)
		data->zoom *= 1.05;
	data_render(data);
	return (0);
}

int	case_jul(int x, int y, t_data *data)
{
	if (!ft_strncmp(data->title, "julia", 5))
	{
		data->julia_x = (map(x, -2, +2, WIDTH) * data->zoom) + \
				data->shift_x;
		data->julia_y = (map(y, +2, -2, HEIGHT) * data->zoom) + \
				data->shift_y;
		data_render(data);
	}
	return (0);
}
