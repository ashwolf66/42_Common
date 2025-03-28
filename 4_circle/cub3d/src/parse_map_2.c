/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:30:59 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:31:00 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_row(char **temp, int i, t_map *map)
{
	temp[i] = (char *)malloc(sizeof(char) * (map->width + 1));
	if (!temp[i])
	{
		free_double(temp);
		return (1);
	}
	ft_memset(temp[i], ' ', map->width);
	temp[i][map->width] = '\0';
	return (0);
}
