/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:22:41 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	*ms_memchr(const void *s, int c, size_t n)
{
	size_t			pos;
	unsigned char	*t_s;

	pos = 0;
	t_s = (unsigned char *)s;
	while (pos < n)
	{
		if (t_s[pos] == (unsigned char)c)
			return (&t_s[pos]);
		++pos;
	}
	return (NULL);
}
