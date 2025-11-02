/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:07:03 by jacha             #+#    #+#             */
/*   Updated: 2025/11/02 10:03:18 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	ssize_t				i;
	const unsigned char	*p;

	p = (const unsigned char *)s;
	i = (ssize_t)ft_strlen(s);
	while (i >= 0)
	{
		if (p[i] == (unsigned char)c)
			return ((char *)&p[i]);
		i--;
	}
	return (0);
}
