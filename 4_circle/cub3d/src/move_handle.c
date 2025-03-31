/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:54:46 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:30:56 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	angle_op(t_data *data, double num)
{
	double	temp_dir;
	double	temp_pla;

	temp_dir = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(SPEED * num) - \
		data->player.dir_y * sin(SPEED * num);
	data->player.dir_y = temp_dir * sin(SPEED * num) + \
		data->player.dir_y * cos(SPEED * num);
	temp_pla = data->player.pla_x;
	data->player.pla_x = data->player.pla_x * cos(SPEED * num) - \
		data->player.pla_y * sin(SPEED * num);
	data->player.pla_y = temp_pla * sin(SPEED * num) + \
		data->player.pla_y * cos(SPEED * num);
}

void	w_s_move(t_data *data)
{
	if (data->player.w == 1)
	{
		data->player.pos_x += data->player.dir_x * SPEED;
		data->player.pos_y += data->player.dir_y * SPEED;
		if (length_check(data))
		{
			data->player.pos_x -= data->player.dir_x * SPEED;
			data->player.pos_y -= data->player.dir_y * SPEED;
		}
	}
	if (data->player.s == 1)
	{
		data->player.pos_x -= data->player.dir_x * SPEED;
		data->player.pos_y -= data->player.dir_y * SPEED;
		if (length_check(data))
		{
			data->player.pos_x += data->player.dir_x * SPEED;
			data->player.pos_y += data->player.dir_y * SPEED;
		}
	}
}

void	a_d_move(t_data *data)
{
	if (data->player.a == 1)
	{
		data->player.pos_x += data->player.dir_y * SPEED;
		data->player.pos_y -= data->player.dir_x * SPEED;
		if (length_check(data))
		{
			data->player.pos_x -= data->player.dir_y * SPEED;
			data->player.pos_y += data->player.dir_x * SPEED;
		}
	}
	if (data->player.d == 1)
	{
		data->player.pos_x -= data->player.dir_y * SPEED;
		data->player.pos_y += data->player.dir_x * SPEED;
		if (length_check(data))
		{
			data->player.pos_x += data->player.dir_y * SPEED;
			data->player.pos_y -= data->player.dir_x * SPEED;
		}
	}
}

void	move_funtion(t_data *data)
{
	if (data->player.w == 1 || data->player.s == 1)
		w_s_move(data);
	if (data->player.a == 1 || data->player.d == 1)
		a_d_move(data);
	if (data->player.left == 1)
		angle_op(data, -1.0);
	if (data->player.right == 1)
		angle_op(data, 1.0);
}
