/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:36:39 by jacha             #+#    #+#             */
/*   Updated: 2024/03/02 19:44:50 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	const char *srcp;

	srcp = src;
	src_len = ft_strlen(src);
	if ((dest == NULL || src == NULL) && size == 0)
		return (0);
	if (dest == NULL || size == 0)
		return (src_len);
	i = 0;
	while (srcp[i] != '\0' && i + 1 < size)
	{
		dest[i] = srcp[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
