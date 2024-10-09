/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strjoin_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:54:45 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/13 08:55:00 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strjoin_s(char *s1, char *s2)
{
	size_t	len;
	size_t	idx;
	char	*new_str;

	idx = 0;
	len = ms_strlen_s(s1) + ms_strlen_s(s2);
	new_str = NULL;
	if (len)
		new_str = (char *)ms_malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	if (s1 != NULL)
		while (*s1)
			new_str[idx++] = *s1++;
	if (s2 != NULL)
		while (*s2)
			new_str[idx++] = *s2++;
	new_str[idx] = '\0';
	return (new_str);
}
