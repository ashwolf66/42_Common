/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:06:29 by jacha             #+#    #+#             */
/*   Updated: 2024/03/05 22:26:22 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	if ((!dest || !src) && !size)
		return (0);
	dest_len = ft_strlen((const char *)dest);
	src_len = ft_strlen((const char *)src);
	if (size < dest_len)
		return (src_len + size);
	while ((dest_len + i + 1) < size && ((char *)src)[i] != '\0')
	{
		dest[dest_len + i] = ((char *)src)[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}
