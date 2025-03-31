/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:44:04 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 15:03:16 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*result_cpy(char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * len + 2);
	while (src[i] != '\n' && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[i++] = '\n';
	}
	dest[i] = '\0';
	return (dest);
}

static char	*cpy(char *dest, char *src, int *i)
{
	while (*src != '\0')
	{
		dest[*i] = *src;
		(*i)++;
		src++;
	}
	return (dest);
}

char	*join(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	int		i;
	char	*result;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		return (ft_strdup(s1));
	}
	s1_len = ft_strlen((const char *)s1);
	s2_len = ft_strlen((const char *)s2);
	result = (char *)malloc(sizeof(char) * s1_len + s2_len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	cpy(result, (char *)s1, &i);
	cpy(result, (char *)s2, &i);
	free ((char *)s1);
	result[i] = '\0';
	return (result);
}

int	find_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
