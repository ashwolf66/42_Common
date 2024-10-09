/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:42:59 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strchr(const char *s, int c)
{
	if (c == '\0')
		return ((char *)&s[ms_strlen(s)]);
	while ((int)*s != c && *s != '\0')
		++s;
	if (*s == '\0')
		return (NULL);
	return ((char *)s);
}
