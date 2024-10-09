/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:20:48 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:48:59 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static int	ms_isspace(int c)
{
	if (('\t' <= c && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	ms_atoi(const char *nptr)
{
	long	result;
	t_bool	isminus;

	result = 0;
	isminus = false;
	while (ms_isspace(*nptr) && *nptr)
		++nptr;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			isminus = true;
		++nptr;
	}
	while (('0' <= (const char)*nptr && (const char)*nptr <= '9') && *nptr)
	{
		result *= 10;
		result += (*nptr - '0');
		++nptr;
	}
	if (isminus)
		return (result * -1);
	return (result);
}
