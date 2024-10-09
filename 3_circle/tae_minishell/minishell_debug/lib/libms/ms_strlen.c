/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:40:00 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:44:08 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

size_t	ms_strlen(const char *s)
{
	char	*start;

	start = (char *)s;
	while (*start != '\0')
		++start;
	return (start - s);
}
