#include "cub3d.h"

void event_handle(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 1L << 17, close_handler, data);
}

int close_handler(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

int key_press(int keysym, t_data *data)
{
	if (keysym == K_ESC)
		close_handler(data);
	else if (keysym == K_W)
		data->player.w = 1;
	else if (keysym == K_S)
		data->player.s = 1;
	else if (keysym == K_A)
		data->player.a = 1;
	else if (keysym == K_D)
		data->player.d = 1;
	else if (keysym == K_LEFT)
		data->player.angle = angle_op(data->player.angle + ANGLE_CHANGE);
	else if (keysym == K_RIGHT)
		data->player.angle = angle_op(data->player.angle - ANGLE_CHANGE);
	return (0);
}

int key_release(int keysym, t_data *data)
{
	if (keysym == K_W)
		data->player.w = 0;
	else if (keysym == K_S)
		data->player.s = 0;
	else if (keysym == K_A)
		data->player.a = 0;
	else if (keysym == K_D)
		data->player.d = 0;
	return (0);
}
