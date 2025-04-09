/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:43:11 by jacha             #+#    #+#             */
/*   Updated: 2025/04/09 18:47:58 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*snap_shot(char *s1)
{
	char	*dest;
	int		i;

	i = 0;
	while (s1[i] != '\n' && s1[i] != '\0')
		i++;
	if (s1[i] == '\n')
		i++;
	dest = ft_strdup(&s1[i]);
	free(s1);
	if (!*dest)
	{
		free(dest);
		dest = NULL;
	}
	return (dest);
}

char	*read_fnc(int fd, char *s1)
{
	char	*temp;
	int		len;

	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
		return (0);
	temp[0] = '\0';
	while (s1 == 0 || find_newline(s1) == -1)
	{
		len = read(fd, temp, BUFFER_SIZE);
		if (len < 0)
		{
			free(temp);
			return (0);
		}
		temp[len] = '\0';
		s1 = join(s1, temp);
		if (!*s1)
		{
			gnl_free_util(s1, temp);
			return (0);
		}
	}
	free(temp);
	return (s1);
}

char	*get_next_line(int fd, t_gnl *gnl)
{
	char			*line;
	int				len;

	if (fd < 0)
		return (0);
	gnl->str = read_fnc(fd, gnl->str);
	if (!gnl->str)
	{
		free(gnl->str);
		gnl->str = NULL;
		return (0);
	}
	len = find_newline(gnl->str);
	line = result_cpy(gnl->str, len);
	gnl->str = snap_shot(gnl->str);
	return (line);
}

void	gnl_free_util(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
