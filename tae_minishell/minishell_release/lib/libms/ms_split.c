/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:39:28 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static size_t	ms_sp_arrlen(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			++cnt;
			while (*s != '\0' && *s != c)
				++s;
		}
		if (*s == '\0')
			break ;
		++s;
	}
	return (cnt);
}

static size_t	ms_sp_strlen(const char *s, char c)
{
	char	*t_s;

	t_s = (char *)s;
	while (*t_s != '\0' && *t_s != c)
		++t_s;
	return ((size_t)(t_s - s));
}

static char	*ms_sp_strdup(const char *s, char c)
{
	size_t	s_len;
	size_t	pos;
	char	*str;

	s_len = ms_sp_strlen(s, c);
	pos = 0;
	str = (char *)ms_malloc(s_len + 1);
	if (str == NULL)
		return (NULL);
	while (s[pos] != '\0' && s[pos] != c)
	{
		str[pos] = s[pos];
		++pos;
	}
	str[pos] = '\0';
	return (str);
}

char	**ms_split(char const *s, char c)
{
	size_t	arrlen;
	size_t	arr_index;
	char	**arr;

	arrlen = ms_sp_arrlen(s, c);
	arr_index = 0;
	arr = (char **)ms_malloc(sizeof(char *) * (arrlen + 1));
	if (arr == NULL)
		return (arr);
	arr[arrlen] = NULL;
	while (arr_index < arrlen)
	{
		if (*s != c)
		{
			arr[arr_index++] = ms_sp_strdup(s, c);
			while (*s != c && *s != '\0')
				++s;
		}
		if (*s == '\0')
			break ;
		++s;
	}
	return (arr);
}
