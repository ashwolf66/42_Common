/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:05:14 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:49:55 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strnstr(const char *big, const char *little, size_t len)
{
	size_t		b_i;
	size_t		l_i;
	size_t		big_len;

	if (little[0] == '\0')
		return ((char *)big);
	big_len = ms_strlen(big);
	if (big_len < len)
		len = big_len;
	b_i = 0;
	while (b_i < len && big[b_i] != '\0')
	{
		l_i = 0;
		if (big[b_i] == little[0])
		{
			while (big[b_i + l_i] == little[l_i] && (b_i + l_i) < len)
				++l_i;
		}
		if (little[l_i] == '\0')
			return ((char *)(&big[b_i]));
		++b_i;
	}
	return (NULL);
}
