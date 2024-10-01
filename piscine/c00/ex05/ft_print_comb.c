/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:21:09 by jacha             #+#    #+#             */
/*   Updated: 2024/01/14 13:58:03 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	third_while(char n1, char n2, char n3)
{
	while (n3 <= '9')
	{
		write(1, &n1, 1);
		write(1, &n2, 1);
		write(1, &n3, 1);
		if (n1 != '7')
		{
			write(1, ", ", 2);
		}
		n3++;
	}
}

void	second_while(char n1, char n2, char n3)
{
	while (n2 <= '8')
	{
		n3 = n2 + 1;
		if (n2 == n1)
		{
			n2++;
		}
		third_while(n1, n2, n3);
		n2++;
	}
}

void	ft_print_comb(void)
{
	char	n1;
	char	n2;
	char	n3;

	n1 = '0';
	while (n1 <= '7')
	{
		n2 = n1 + 1;
		n3 = '0';
		second_while(n1, n2, n3);
		n1++;
	}
}
