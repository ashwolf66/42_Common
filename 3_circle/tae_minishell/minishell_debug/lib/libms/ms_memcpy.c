/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:07:49 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"
#include <stdio.h>

void	*ms_memcpy(void *dest, const void *src, size_t n)
{
	size_t	pos;

	pos = 0;
	if (dest == NULL && src == NULL)
		return (dest);
	while (pos < n)
	{
		((char *)dest)[pos] = ((char *)src)[pos];
		++pos;
	}
	return (dest);
}
