/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:30:31 by jacha             #+#    #+#             */
/*   Updated: 2025/11/02 10:03:31 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t				i;
	const unsigned char	*p;

	p = (const unsigned char *)s;
	i = 0;
	while (p[i])
	{
		if (p[i] == (unsigned char)c)
			return ((char *)&p[i]);
		i++;
	}
	if (p[i] == (unsigned char)c)
		return ((char *)&p[i]);
	return (0);
}
