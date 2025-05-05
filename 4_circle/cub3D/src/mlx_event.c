/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:54:36 by jacha             #+#    #+#             */
/*   Updated: 2025/04/09 18:44:59 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event_handle(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 1L << 17, close_handler, data);
	mlx_loop_hook(data->mlx, refresh_map, data);
}

int	close_handler(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->map->texture[i].img.img)
			mlx_destroy_image(data->mlx, data->map->texture[i].img.img);
		i++;
	}
	free_map(data->map);
	free_mlx_data(data);
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	key_press(int keysym, t_data *data)
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
		data->player.left = 1;
	else if (keysym == K_RIGHT)
		data->player.right = 1;
	return (0);
}

int	key_release(int keysym, t_data *data)
{
	if (keysym == K_W)
		data->player.w = 0;
	else if (keysym == K_S)
		data->player.s = 0;
	else if (keysym == K_A)
		data->player.a = 0;
	else if (keysym == K_D)
		data->player.d = 0;
	else if (keysym == K_LEFT)
		data->player.left = 0;
	else if (keysym == K_RIGHT)
		data->player.right = 0;
	return (0);
}
