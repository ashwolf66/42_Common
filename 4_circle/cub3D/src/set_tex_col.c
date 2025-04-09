/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:31:10 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:33:17 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_texture(char *line, t_map *map, int direct)
{
	char	**temp;

	if (map->texture[direct].path)
		return (1);
	line += 2;
	temp = ft_split(line, ' ');
	if (!temp || !temp[0] || temp[1])
	{
		free_double(temp);
		return (1);
	}
	map->texture[direct].path = ft_strdup(temp[0]);
	free_double(temp);
	if (!map->texture[direct].path)
		return (1);
	return (0);
}

int	set_color(char *line, t_color *color, t_map *map, char chr)
{
	char	**temp;

	if ((chr == 'F' && map->floor.color != -1) || \
	(chr == 'C' && map->ceiling.color != -1))
		return (1);
	line += 1;
	operation_line_space_color(&line);
	temp = ft_split(line, ',');
	if (!temp || !temp[0] || !temp[1] || !temp[2] || temp[3])
	{
		free_double(temp);
		return (1);
	}
	if (alloc_color(temp, color, map))
		return (1);
	return (0);
}

int	alloc_color(char **colors, t_color *color, t_map *map)
{
	int	r;
	int	g;
	int	b;

	(void) map;
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_double(colors);
		return (1);
	}
	color->color = (r << 16) | (g << 8) | b;
	free_double(colors);
	return (0);
}
