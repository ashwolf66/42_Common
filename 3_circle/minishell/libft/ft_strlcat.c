/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:45:49 by hchin             #+#    #+#             */
/*   Updated: 2024/02/27 14:39:04 by hchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	index;
	size_t	destlen;
	size_t	srclen;

	index = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size < destlen + 1)
	{
		return (srclen + size);
	}
	while (destlen + 1 + index < size && src[index] != '\0')
	{
		dest[index + destlen] = src[index];
		index++;
	}
	dest[destlen + index] = '\0';
	return (destlen + srclen);
}
