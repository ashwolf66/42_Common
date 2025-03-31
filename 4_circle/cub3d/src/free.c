/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:29:54 by jacha             #+#    #+#             */
/*   Updated: 2025/03/31 16:51:19 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->map)
	{
		i = 0;
		while (i < 4)
		{
			if (data->map->texture[i].path)
				free(data->map->texture[i].path);
			if (data->map->texture[i].img.img)
				mlx_destroy_image(data->mlx, data->map->texture[i].img.img);
			i++;
		}
		if (data->map->cub_map)
		{
			i = 0;
			while (i < 4)
			{
				free(data->map->cub_map[i]);
				i++;
			}
			free(data->map->cub_map);
		}
		free(data->map);
	}
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_texture(map);
	free_cubmap(map);
	free(map);
}

void	free_texture(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < 4)
	{
		if (map->texture[i].path)
		{
			free(map->texture[i].path);
			map->texture[i].path = NULL;
		}
		i++;
	}
}

void	free_cubmap(t_map *map)
{
	int	i;

	if (!map || !map->cub_map)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->cub_map[i])
		{
			free(map->cub_map[i]);
			map->cub_map[i] = NULL;
		}
		i++;
	}
	free(map->cub_map);
	map->cub_map = NULL;
}
