/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:30:32 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:38:58 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	operation_line_end_space(char **line)
{
	size_t	len;

	len = ft_strlen(*line);
	while (len > 0 && ((*line)[len - 1] == '\n' || \
				(*line)[len - 1] == '\t' || (*line)[len - 1] == ' '))
	{
		(*line)[len - 1] = '\0';
		len--;
	}
}

void	operation_line_start_space(char **line)
{
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
}

void	operation_line_space_color(char **line)
{
	char	*src;
	char	*dst;

	src = *line;
	dst = *line;
	while (*src)
	{
		if (*src != ' ' && *src != '\t' && *src != '\n')
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
}
