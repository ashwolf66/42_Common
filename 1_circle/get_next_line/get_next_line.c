/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:43:11 by jacha             #+#    #+#             */
/*   Updated: 2024/04/01 16:00:44 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(s);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (temp == NULL)
		return (0);
	while (((char *)s)[i] != '\0')
	{
		temp[i] = ((char *)s)[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

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
	return (dest);
}

char	*read_fnc(int fd, char *s1)
{
	char	*temp;
	int		len;

	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
	{
		free(s1);
		return (0);
	}
	temp[0] = '\0';
	while (s1 == 0 || find_newline(s1) == -1)
	{
		len = read(fd, temp, BUFFER_SIZE);
		temp[len] = '\0';
		s1 = join(s1, temp);
		if (!*s1)
		{
			free(temp);
			free(s1);
			return (0);
		}
	}
	free(temp);
	return (s1);
}

char	*get_next_line(int fd)
{
	static char		*file_read;
	char			*line;
	int				len;

	if (fd < 0)
		return (0);
	file_read = read_fnc(fd, file_read);
	if (!file_read)
		return (0);
	len = find_newline(file_read);
	line = result_cpy(file_read, len);
	file_read = snap_shot(file_read);
	return (line);
}
