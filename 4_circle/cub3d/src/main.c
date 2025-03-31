/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:56:49 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 15:04:49 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	*map;
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	map = NULL;
	if (argv_check(ac, av[1]))
	{
		free(data);
		return (1);
	}
	map = init_map(av[1]);
	if (!map)
	{
		free(data);
		return (1);
	}
	if (mlx_start(data, map))
		return (1);
	key_init(data);
	player_init(data);
	event_handle(data);
	mlx_loop_hook(data->mlx, refresh_map, data);
	mlx_loop((*data).mlx);
	return (0);
}

int	refresh_map(t_data *data)
{
	move_funtion(data);
	fill_background(data);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

void	fill_background(t_data *data)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		dst = data->img.addr + y * data->img.line_length;
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < (WIN_HEIGHT / 2))
				*(unsigned int *)(dst + x * (data->img.bit_per_pixel / 8))
					= data->map->ceiling.color;
			else
				*(unsigned int *)(dst + x * (data->img.bit_per_pixel / 8))
					= data->map->floor.color;
			x++;
		}
		y++;
	}
}
