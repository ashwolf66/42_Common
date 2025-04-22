/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:31:12 by jacha             #+#    #+#             */
/*   Updated: 2025/04/22 13:42:39 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_set(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (single_texture_set(data, i))
		{
			while (i >= 0)
			{
				if (data->map->texture[i].img.img)
					mlx_destroy_image(data->mlx, data->map->texture[i].img.img);
				i--;
			}
			free_mlx_data(data);
			free_map(data->map);
			free_data(data);
			return (1);
		}
		i++;
	}
	key_init(data);
	player_init(data);
	return (0);
}

int	single_texture_set(t_data *data, int i)
{
	data->map->texture[i].img.img = mlx_xpm_file_to_image(data->mlx,
			data->map->texture[i].path,
			&data->map->texture[i].img.width,
			&data->map->texture[i].img.height);
	if (!data->map->texture[i].img.img)
	{
		return (1);
	}
	data->map->texture[i].img.addr = mlx_get_data_addr \
(data->map->texture[i].img.img,
			&data->map->texture[i].img.bit_per_pixel,
			&data->map->texture[i].img.line_length,
			&data->map->texture[i].img.endian);
	if (!data->map->texture[i].img.addr)
	{
		return (1);
	}
	return (0);
}
