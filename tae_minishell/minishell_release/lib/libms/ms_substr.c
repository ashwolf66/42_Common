/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:34:14 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static char	*ms_substrdup(char const *s, size_t len)
{
	size_t	pos;
	char	*str;

	pos = 0;
	str = (char *)ms_malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (pos < len)
	{
		str[pos] = s[pos];
		++pos;
	}
	str[pos] = '\0';
	return (str);
}

char	*ms_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	size_t			ptrdiff;
	char			*res;

	s_len = ms_strlen(s);
	res = NULL;
	if (start >= s_len)
	{
		res = (char *)ms_malloc(sizeof(char) * 1);
		if (res == NULL)
			return (NULL);
		res[0] = '\0';
	}
	else
	{
		ptrdiff = (s_len - start);
		if (ptrdiff < len)
			len = ptrdiff;
		res = ms_substrdup((char const *)(&s[start]), len);
	}
	return (res);
}
