/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 22:03:51 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:44:08 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*ms_memmove(void *dest, const void *src, size_t n)
{
	size_t		pos;
	char		*cp_dest;
	const char	*cp_src;

	pos = 0;
	if (n == 0)
		return (dest);
	if (dest < src)
		return (ms_memcpy(dest, src, n));
	else if (dest > src)
	{
		cp_dest = (char *)dest + (n - 1);
		cp_src = (const char *)src + (n - 1);
		while (pos < n)
		{
			*(cp_dest - pos) = *(cp_src - pos);
			++pos;
		}
	}
	return (dest);
}
