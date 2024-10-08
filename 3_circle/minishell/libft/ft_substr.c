/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:22:55 by jacha             #+#    #+#             */
/*   Updated: 2024/03/05 15:47:34 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	s_len;
	char			*result;

	i = 0;
	if (!s)
		return (0);
	s_len = ft_strlen((const char *)s);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (0);
	while ((s_len > start && ((char *)s)[start] != '\0') && i < len)
	{
		result[i] = ((char *)s)[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}
