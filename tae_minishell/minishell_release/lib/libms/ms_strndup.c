/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:41:33 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/10 16:39:05 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strndup(const char *s, size_t n)
{
	size_t	pos;
	char	*str;

	pos = 0;
	str = (char *)ms_malloc(n + 1);
	if (str == NULL)
		return (NULL);
	while (pos < n)
	{
		str[pos] = s[pos];
		++pos;
	}
	str[pos] = '\0';
	return (str);
}
