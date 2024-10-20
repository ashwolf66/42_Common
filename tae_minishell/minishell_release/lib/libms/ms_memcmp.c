/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:41:51 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:44:08 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int	ms_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			pos;
	unsigned char	*t_s1;
	unsigned char	*t_s2;

	t_s1 = (unsigned char *)s1;
	t_s2 = (unsigned char *)s2;
	pos = 0;
	while (pos < n)
	{
		if (t_s1[pos] != t_s2[pos])
			return ((int)(t_s1[pos]) - (int)(t_s2[pos]));
		++pos;
	}
	return (0);
}
