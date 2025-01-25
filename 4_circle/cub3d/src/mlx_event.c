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
		data->player.py -= 8.0;
	else if (keysym == K_S)
		data->player.py += 8.0;
	else if (keysym == K_A)
		data->player.px -= 8.0;
	else if (keysym == K_D)
		data->player.px += 8.0;
	else if (keysym == K_LEFT)
		data->player.key = K_LEFT;
	else if (keysym == K_RIGHT)
		data->player.key = K_RIGHT;
	if (data->player.py >= 448)
		data->player.py -= 8.0;
	else if (data->player.py <= 0)
		data->player.py += 8.0;
	if (data->player.px >= 822)
		data->player.px -= 8.0;
	else if (data->player.px <= 0)
		data->player.px += 8.0;
	draw_square(data, data->player.px, data->player.py, 0x00FF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int	key_release(int keysym, t_data *data)
{
	(void)keysym;
	(void)data;
	return (0);
}

