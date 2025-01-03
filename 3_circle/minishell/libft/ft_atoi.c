/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:35:22 by hchin             #+#    #+#             */
/*   Updated: 2024/12/31 09:40:52 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *n)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((n[i] == 32) || ((n[i] > 8) && (n[i] < 14)))
		i++;
	if ((n[i] == '+') || (n[i] == '-'))
	{
		if (n[i] == '-')
			sign = sign * -1;
		i++;
	}
	while ((n[i] >= '0') && (n[i] <= '9'))
	{
		result = result * 10;
		result = result + (n[i] - '0');
		i++;
	}
	return (result * sign);
}
