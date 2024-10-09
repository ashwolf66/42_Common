/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:42:53 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strdup(const char *s)
{
	size_t	s_len;
	size_t	pos;
	char	*str;

	s_len = ms_strlen(s);
	pos = 0;
	str = (char *)ms_malloc(s_len + 1);
	if (str == NULL)
		return (NULL);
	while (s[pos] != '\0')
	{
		str[pos] = s[pos];
		++pos;
	}
	str[pos] = '\0';
	return (str);
}
