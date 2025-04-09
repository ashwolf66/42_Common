/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:31:01 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:35:38 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_cub_map(char **lines, t_map *map)
{
	if (!lines || !map)
		return (1);
	map->height = check_map_height(lines);
	if (map->height < 3)
		return (1);
	map->width = check_map_width(lines);
	if (map->width < 3)
		return (1);
	map->cub_map = create_cub_map(lines, map);
	if (!map->cub_map)
		return (1);
	if (cub_map_validate(map))
		return (1);
	return (0);
}

int	check_map_height(char **lines)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 0)
			count++;
		i++;
	}
	return (count);
}

int	check_map_width(char **lines)
{
	int	max;
	int	temp;
	int	i;

	max = 0;
	i = 0;
	while (lines[i])
	{
		temp = ft_strlen(lines[i]);
		if (max <= temp)
			max = temp;
		i++;
	}
	return (max);
}

char	**create_cub_map(char **lines, t_map *map)
{
	char	**temp;
	int		i;
	int		j;

	temp = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		if (init_row(temp, i, map))
			return (NULL);
		j = 0;
		while (lines[i][j] && j < map->width)
		{
			temp[i][j] = lines[i][j];
			j++;
		}
		i++;
	}
	temp[map->height] = NULL;
	return (temp);
}
