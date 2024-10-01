/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush04.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:08:57 by jacha             #+#    #+#             */
/*   Updated: 2024/01/17 12:04:00 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

extern	void	ft_putchar(char c);

void	each_case(int c, int r, int col, int row)
{
	if (r == 0 && c == 0)
		ft_putchar('A');
	else if (r == row - 1 && c == 0)
		ft_putchar('C');
	if ((r == 0 || r == row - 1) && (c != 0 && c != col -1))
		ft_putchar('B');
	else if ((r != 0 && r != row - 1) && (c == 0 || c == col - 1))
		ft_putchar('B');
	if (r != 0 && r != row - 1)
	{
		if (c != 0 && c != col -1)
		{
			ft_putchar(' ');
		}
	}
	if ((col > 1) && (r == 0 && c == col - 1))
		ft_putchar('C');
	else if ((col > 1) && (r == row - 1 && c == col - 1))
		ft_putchar('A');
}

void	rush(int col, int row)
{
	int	c;
	int	r;

	if (col < 1 || row < 1)
	{
		ft_putchar('D');
		return ;
	}
	r = 0;
	while (r < row)
	{
		c = 0;
		while (c < col)
		{
			each_case(c, r, col, row);
			c++;
		}
		ft_putchar('\n');
		r++;
	}
}
