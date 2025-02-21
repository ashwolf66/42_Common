#include "cub3d.h"

double angle_op(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0.0)
		angle += 2.0 * M_PI;
	return (angle);
}

void w_s_move(t_data *data)
{
	if (data->player.w == 1)
	{
		data->player.px += cos(data->player.angle) * SPEED;
		data->player.py += sin(data->player.angle) * SPEED;
		if (length_check(data))
		{
			data->player.px -= cos(data->player.angle) * SPEED;
			data->player.py -= sin(data->player.angle) * SPEED;
		}
	}
	if (data->player.s == 1)
	{
		data->player.px -= cos(data->player.angle) * SPEED;
		data->player.py -= sin(data->player.angle) * SPEED;
		if (length_check(data))
		{
			data->player.px += cos(data->player.angle) * SPEED;
			data->player.py += sin(data->player.angle) * SPEED;
		}
	}
}

void a_d_move(t_data *data)
{
	if (data->player.a == 1)
	{
		data->player.px -= cos(data->player.angle + M_PI / 2.0) * SPEED;
		data->player.py -= sin(data->player.angle + M_PI / 2.0) * SPEED;
		if (length_check(data))
		{
			data->player.px += cos(data->player.angle + M_PI / 2.0) * SPEED;
			data->player.py += sin(data->player.angle + M_PI / 2.0) * SPEED;
		}
	}
	if (data->player.d == 1)
	{
		data->player.px += cos(data->player.angle + M_PI / 2.0) * SPEED;
		data->player.py += sin(data->player.angle + M_PI / 2.0) * SPEED;
		if (length_check(data))
		{
			data->player.px -= cos(data->player.angle + M_PI / 2.0) * SPEED;
			data->player.py -= sin(data->player.angle + M_PI / 2.0) * SPEED;
		}
	}
}

int length_check(t_data *data)
{
	int map_pixel_width;
	int map_pixel_height;

	map_pixel_width = data->map.width * TILE_SIZE;
	map_pixel_height = data->map.height * TILE_SIZE;
	if (data->player.px < 0 || data->player.py < 0 || data->player.px >= map_pixel_width || data->player.py >= map_pixel_height)
	{
		return (1);
	}
	return (0);
}

void	move_funtion(t_data *data)
{
	if (data->player.w == 1 || data->player.s == 1)
		w_s_move(data);
	if (data->player.a == 1 || data->player.d == 1)
		a_d_move(data);
	if (data->player.left == 1)
		data->player.angle = angle_op(data->player.angle - ANGLE_CHANGE);
	if (data->player.right == 1)
		data->player.angle = angle_op(data->player.angle + ANGLE_CHANGE);
}
