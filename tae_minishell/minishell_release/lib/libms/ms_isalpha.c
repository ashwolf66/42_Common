/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:40:52 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:45:29 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static int	ms_isupper(int c)
{
	if ('A' <= c && c <= 'Z')
		return (MS_UP);
	return (0);
}

static int	ms_islower(int c)
{
	if ('a' <= c && c <= 'z')
		return (MS_LO);
	return (0);
}

int	ms_isalpha(int c)
{
	if (ms_isupper(c) || ms_islower(c))
		return (MS_AL);
	return (0);
}
