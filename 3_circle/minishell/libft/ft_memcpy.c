/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:01:33 by hchin             #+#    #+#             */
/*   Updated: 2024/02/26 17:24:44 by hchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
/*
	size_t	i;
	char *d;

	i = 0;
	d = (char *)dest;
	if (!dest || !src)
		return (0);
	if (dest == src)
		return (dest);
	while (i < n)
	{
		d[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
*/
