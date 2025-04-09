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

int	argv_check(int ac, char *map_file)
{
	if (ac != 2)
		return (1);
	if (extension_check(map_file, ".cub"))
		return (1);
	if (file_check(map_file))
		return (1);
	return (0);
}

int	extension_check(char *map_file, char *cub)
{
	int	file_len;
	int	ext_len;

	file_len = ft_strlen(map_file);
	ext_len = ft_strlen(cub);
	if (file_len <= ext_len)
		return (1);
	if (ft_strncmp(map_file + file_len - ext_len, cub, ext_len) != 0)
		return (1);
	return (0);
}

int	file_check(char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
