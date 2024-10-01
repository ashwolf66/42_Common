/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:39:35 by jacha             #+#    #+#             */
/*   Updated: 2024/03/05 15:50:31 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	int		i;
	char	*result;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen((const char *)s1);
	s2_len = ft_strlen((const char *)s2);
	result = (char *)malloc(sizeof(char) * s1_len + s2_len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	cpy(result, (char *)s1, &i);
	cpy(result, (char *)s2, &i);
	result[i] = '\0';
	return (result);
}
