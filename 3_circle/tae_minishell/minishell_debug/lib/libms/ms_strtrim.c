/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:09:13 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:49:16 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static t_bool	ms_isset(const char c, char const *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (true);
		++set;
	}
	return (false);
}

char	*ms_strtrim(char const *s1, char const *set)
{
	size_t	s1_end;
	size_t	str_len;
	size_t	pos;
	char	*str;

	while (ms_isset(*s1, set) && *s1 != '\0')
		++s1;
	s1_end = ms_strlen(s1) - 1;
	while (ms_isset(s1[s1_end], set) && (&s1[s1_end] >= s1))
		--s1_end;
	str_len = (&s1[s1_end] - s1 + 1);
	str = (char *)ms_malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	pos = 0;
	while (pos < str_len)
	{
		str[pos] = s1[pos];
		++pos;
	}
	str[pos] = '\0';
	return (str);
}
