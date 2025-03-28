/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:28:46 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:30:15 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	argv_check(int ac, char *map_file, t_map *map, t_data *data)
{
	if (ac != 2)
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	if (extension_check(map_file, ".cub"))
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	if (file_check(map_file, map, data))
		return (1);
	return (0);
}

int	extension_check(char *map_file, char *cub)
{
	int	file_len;
	int	ext_len;

	file_len = ft_strlen(map_file);
	ext_len = ft_strlen(cub);
	while (file_len > 0)
	{
		if (ext_len == 0)
			break ;
		if (map_file[file_len - 1] != cub[ext_len - 1])
			return (1);
		ext_len--;
		file_len--;
	}
	if (file_len < 1)
		return (1);
	return (0);
}

int	file_check(char *map_file, t_map *map, t_data *data)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		free_map(map);
		free_data(data);
		return (1);
	}
	close(fd);
	return (0);
}
