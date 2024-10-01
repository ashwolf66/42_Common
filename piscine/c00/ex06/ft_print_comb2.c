/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:59:41 by jacha             #+#    #+#             */
/*   Updated: 2024/01/17 14:55:44 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	div_1(int num)
{
	char	temp1;
	char	temp2;
	int		front;
	int		end;

	if (num < 10)
	{
		write(1, "0", 1);
		temp1 = '0' + num;
		write(1, &temp1, 1);
	}
	else
	{
		front = num / 10;
		end = num % 10;
		temp1 = front + '0';
		temp2 = end + '0';
		write(1, &temp1, 1);
		write(1, &temp2, 1);
	}
}

void	ft_print_comb2(void)
{
	int	n1;
	int	n2;

	n1 = 0;
	n2 = 0;
	while (n1 <= 99)
	{
		n2 = n1 + 1;
		while (n2 <= 99)
		{
			div_1(n1);
			write(1, " ", 1);
			div_1(n2);
			if (n1 < 98)
			{
				write(1, ", ", 2);
			}
			n2++;
		}
		n1++;
	}
}
