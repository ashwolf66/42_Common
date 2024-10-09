/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:45:22 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:44:08 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

size_t	ms_strlcat(char *dst, const char *src, size_t sz)
{
	size_t	pos;
	size_t	src_len;
	size_t	dst_len;

	pos = 0;
	while (pos < sz && dst[pos] != '\0')
		++pos;
	src_len = ms_strlen(src);
	if (pos == sz)
		return (sz + src_len);
	dst_len = ms_strlen(dst);
	pos = 0;
	while (pos < (sz - dst_len - 1) && src[pos])
	{
		dst[dst_len + pos] = src[pos];
		++pos;
	}
	dst[dst_len + pos] = '\0';
	return (src_len + dst_len);
}
