/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:43:07 by jacha             #+#    #+#             */
/*   Updated: 2024/01/21 19:39:48 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	my_comb(int n, char i, char *a, int *o)
{
	int	num;

	while (i <= (10 - n) + '0')
	{
		a[*o - n] = i;
		if (n == 1)
		{
			num = 0;
			while (num <= *o - n)
			{
				write(1, &a[num], 1);
				num++;
			}
			if (a[0] != '0' + (10 - *o))
			{
				write(1, ", ", 2);
			}
		}
		if (n - 1 != 0)
		{
			my_comb(n - 1, i + 1, a, o);
		}
		i++;
	}
}

void	ft_print_combn(int n)
{
	char	c;
	char	a[10];
	int		*o;

	c = '0';
	o = &n;
	my_comb(n, c, a, o);
}
