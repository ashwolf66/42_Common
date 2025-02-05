#include "cub3d.h"

void	event_handle(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 1L << 17, close_handler, data);
}

int	close_handler(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

int key_press(int keysym, t_data *data)
{
	draw_square(data, data->player.px, data->player.py, 0x00000000);
	if (keysym == K_ESC)
		close_handler(data);
	else if (keysym == K_W)
	{
		data->player.px += cos(data->player.angle) * SPEED;
		data->player.py -= sin(data->player.angle) * SPEED;
	}
	else if (keysym == K_S)
	{
		data->player.px -= cos(data->player.angle) * SPEED;
		data->player.py += sin(data->player.angle) * SPEED;
	}
	else if (keysym == K_A)
	{
		data->player.px -= cos(data->player.angle - (float)M_PI / 2) * SPEED;
		data->player.py += sin(data->player.angle - (float)M_PI / 2) * SPEED;
	}
	else if (keysym == K_D)
	{
		data->player.px += cos(data->player.angle - (float)M_PI / 2) * SPEED;
		data->player.py -= sin(data->player.angle - (float)M_PI / 2) * SPEED;
	}

	else if (keysym == K_LEFT)
		data->player.angle = angle_op(data->player.angle + ANGLE_CHANGE);
	else if (keysym == K_RIGHT)
		data->player.angle = angle_op(data->player.angle - ANGLE_CHANGE);
	return (0);
}

float angle_op(float angle)
{
	angle = fmod(angle, 2.0f * M_PI);
	if (angle < 0.0f)
		angle += 2.0f * M_PI;
	return (angle);
}

int	key_release(int keysym, t_data *data)
{
	(void)keysym;
	(void)data;
	return (0);
}
