/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:31:22 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

char	*ms_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	pos;

	str = (char *)ms_malloc(sizeof(char) * (ms_strlen(s) + 1));
	pos = 0;
	if (str == NULL)
		return (str);
	while (s[pos] != '\0')
	{
		str[pos] = f(pos, s[pos]);
		++pos;
	}
	str[pos] = '\0';
	return (str);
}
