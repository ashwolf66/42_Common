/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:21:20 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:44:08 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int	ms_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			pos;
	unsigned char	*t_s1;
	unsigned char	*t_s2;

	pos = 0;
	t_s1 = (unsigned char *)s1;
	t_s2 = (unsigned char *)s2;
	if (pos == n)
		return (0);
	while (pos < n - 1 && *t_s1 && *t_s2 && *t_s1 == *t_s2)
	{
		++t_s1;
		++t_s2;
		++pos;
	}
	return ((int)(*t_s1) - (int)(*t_s2));
}
