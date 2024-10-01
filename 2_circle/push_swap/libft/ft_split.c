/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:26:44 by jacha             #+#    #+#             */
/*   Updated: 2024/05/21 14:39:40 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	row_len(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			len++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (len);
}

static size_t	colum_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static char	free_mal(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

static int	cpy_contents(char **result, char const *s, char c, size_t row)
{
	size_t	colum;
	size_t	i;

	i = 0;
	while (i < row)
	{
		while (*s == c)
			s++;
		colum = colum_len(s, c);
		result[i] = (char *)malloc(sizeof(char) * colum + 1);
		if (!result[i])
			return (free_mal(result));
		ft_strlcpy(result[i], s, colum + 1);
		i++;
		s += colum;
	}
	result[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	row;

	if (!s)
		return (0);
	row = row_len(s, c);
	result = (char **)malloc(sizeof(char *) * (row + 1));
	if (!result)
	{
		free (result);
		return (0);
	}
	if (cpy_contents(result, s, c, row) == 0)
		return (0);
	return (result);
}
