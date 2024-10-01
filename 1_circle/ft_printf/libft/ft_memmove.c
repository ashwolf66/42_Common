/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:19:43 by jacha             #+#    #+#             */
/*   Updated: 2024/03/06 21:35:31 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t	i;

	i = count;
	if (dest == NULL && src == NULL)
		return (dest);
	if ((unsigned char *)dest > (unsigned char *)src)
	{
		while (i > 0)
		{
			((unsigned char *)dest)[i - 1] = ((char *)src)[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, count);
	return (dest);
}
