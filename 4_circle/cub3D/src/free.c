/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:29:54 by jacha             #+#    #+#             */
/*   Updated: 2025/04/05 16:05:05 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free(data);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->cub_map)
		free_cub_map(map);
	free_texture(map);
	free(map);
}

void	free_cub_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->cub_map[i])
	{
		free(map->cub_map[i]);
		map->cub_map[i] = NULL;
		i++;
	}
	free(map->cub_map);
	map->cub_map = NULL;
}

void	free_texture(t_map *map)
{
	int	i;

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
