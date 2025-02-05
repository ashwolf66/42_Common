#include "cub3d.h"

float angle_op(float angle)
{
	angle = fmod(angle, 2.0f * M_PI);
	if (angle < 0.0f)
		angle += 2.0f * M_PI;
	return (angle);
}

void w_s_move(int keysym, t_data *data)
{
	if (keysym == K_W)
	{
		data->player.px += (float)cos(data->player.angle) * SPEED;
		data->player.py -= (float)sin(data->player.angle) * SPEED;
	}
	else if (keysym == K_S)
	{
		data->player.px -= (float)cos(data->player.angle) * SPEED;
		data->player.py += (float)sin(data->player.angle) * SPEED;
	}
}

void a_d_move(int keysym, t_data *data)
{
	if (keysym == K_A)
	{
		data->player.px -= (float)cos(data->player.angle - \
        (float)M_PI / 2.0f) * SPEED;
		data->player.py += (float)sin(data->player.angle - \
        (float)M_PI / 2.0f) * SPEED;
	}
	else if (keysym == K_D)
	{
		data->player.px += (float)cos(data->player.angle - \
        (float)M_PI / 2.0f) * SPEED;
		data->player.py -= (float)sin(data->player.angle - \
        (float)M_PI / 2.0f) * SPEED;
	}
}
