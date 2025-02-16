/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:56:49 by jacha             #+#    #+#             */
/*   Updated: 2025/01/18 16:57:10 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	(void)av;
	mlx_start(&data);
	event_handle(&data);
	mlx_loop_hook(data.mlx, refresh_map, &data);
	mlx_loop(data.mlx);
	return (0);
}

int refresh_map(t_data *data)
{
	draw_square(data, data->player.px, data->player.py, 0x00000000);
	move_funtion(data);
	draw_square(data, data->player.px, data->player.py, 0x00FF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    return (0);
}

void	move_funtion(t_data *data)
{
	if (data->player.w == 1 || data->player.s == 1)
		w_s_move(data);
	if (data->player.a == 1 || data->player.d == 1)
		a_d_move(data);
	if (data->player.left == 1)
		data->player.angle = angle_op(data->player.angle + ANGLE_CHANGE);
	if (data->player.right == 1)
		data->player.angle = angle_op(data->player.angle - ANGLE_CHANGE);
}
