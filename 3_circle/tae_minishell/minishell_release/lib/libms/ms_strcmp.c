/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:37:10 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/10 12:38:30 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int	ms_strcmp(const char *s1, const char *s2)
{
	size_t	idx;

	idx = 0;
	while (s1[idx] && s2[idx])
	{
		if (s1[idx] != s2[idx])
			break ;
		++idx;
	}
	return ((int)(s1[idx] - s2[idx]));
}
