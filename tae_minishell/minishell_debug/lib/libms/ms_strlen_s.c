/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strlen_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:54:18 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/13 08:54:24 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

size_t	ms_strlen_s(char *str)
{
	char	*t_str;

	if (str == NULL)
		return (0);
	t_str = str;
	while (*t_str != '\0')
		t_str++;
	return ((size_t)(t_str - str));
}
