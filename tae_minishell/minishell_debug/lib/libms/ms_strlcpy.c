/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:22:32 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:44:08 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

size_t	ms_strlcpy(char *dst, const char *src, size_t sz)
{
	size_t	src_len;
	size_t	pos;

	src_len = ms_strlen(src);
	pos = 0;
	if (sz > 0)
	{
		while (pos < sz - 1 && src[pos] != '\0')
		{
			dst[pos] = src[pos];
			++pos;
		}
		dst[pos] = '\0';
	}
	return (src_len);
}
