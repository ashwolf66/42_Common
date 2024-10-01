/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:39:04 by jacha             #+#    #+#             */
/*   Updated: 2024/03/05 21:28:50 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atol(const char *n)
{
	long long int	i;
	long long int	num;
	long long int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((((char *)n)[i] >= 9 && ((char *)n)[i] <= 13) || \
			((char *)n)[i] == 32)
		i++;
	if (((char *)n)[i] == '+' || ((char *)n)[i] == '-')
	{
		if (((char *)n)[i] == '-')
			sign = -1;
		i++;
	}
	while (((char *)n)[i] >= '0' && ((char *)n)[i] <= '9')
	{
		num = num * 10 + (((char *)n)[i] - '0');
		i++;
	}
	return (num * sign);
}
