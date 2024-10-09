/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:50:48 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:46:52 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static size_t	ms_intlen(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		++len;
	while (n != 0 && (n >= 10 || n <= -10))
	{
		++len;
		n /= 10;
	}
	return (len);
}

static void	ms_putnbr(int n, char *res, size_t nmemb)
{
	if (n < 0)
		res[nmemb] = (-(n % 10)) + '0';
	else
		res[nmemb] = (n % 10) + '0';
	if (nmemb == 0)
		return ;
	ms_putnbr(n / 10, res, nmemb - 1);
}

char	*ms_itoa(int n)
{
	size_t	intlen;
	char	*res;

	intlen = ms_intlen(n);
	res = (char *)ms_malloc(sizeof(char) * (intlen + 1));
	if (res == NULL)
		return (res);
	ms_putnbr(n, res, intlen - 1);
	if (n < 0)
		res[0] = '-';
	res[intlen] = '\0';
	return (res);
}
