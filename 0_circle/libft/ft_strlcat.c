/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:06:29 by jacha             #+#    #+#             */
/*   Updated: 2025/11/02 09:56:53 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		dest_len;
	size_t		src_len;
	size_t		i;
	const char	*srcp;

	i = 0;
	if ((!dest || !src) && !size)
		return (0);
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size < dest_len)
		return (src_len + size);
	srcp = src;
	while (dest_len + i + 1 < size && srcp[i] != '\0')
	{
		dest[dest_len + i] = srcp[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}
