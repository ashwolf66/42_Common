#include "cub3d.h"

void	event_init(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_handler, data);
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

int	key_handler(int keysym, t_data *data)
{
	if (keysym == 65307)
		close_handler(data);
	return (0);
}

/*
119		=	"w"
97		=	"a"
115		=	"s"
100		=	"d"
65361	=	"LEFT"
65362	=	"UP"
65363	=	"RIGHT"
65364	=	"DOWN"
*/
