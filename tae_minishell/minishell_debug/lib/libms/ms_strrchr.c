/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:29:37 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"
#include <stdio.h>

char	*ms_strrchr(const char *s, int c)
{
	char	*t_s;
	size_t	s_len;

	s_len = ms_strlen(s);
	if (c == '\0')
		return ((char *)&s[s_len]);
	t_s = (char *)s + (s_len - 1);
	while (t_s >= s)
	{
		if (*t_s == (const char)c)
			return (t_s);
		--t_s;
	}
	return (NULL);
}
