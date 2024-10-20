/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:45:34 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	pos;
	char	*str;

	s1_len = ms_strlen(s1);
	s2_len = ms_strlen(s2);
	pos = 0;
	str = (char *)ms_malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == NULL)
		return (str);
	while (pos < s1_len)
	{
		str[pos] = *s1++;
		++pos;
	}
	s2_len += s1_len;
	while (pos < s2_len)
	{
		str[pos] = *s2++;
		++pos;
	}
	str[pos] = '\0';
	return (str);
}
