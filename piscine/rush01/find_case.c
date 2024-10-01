/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:53:07 by jacha             #+#    #+#             */
/*   Updated: 2024/01/23 17:26:04 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

extern void	putchr(char c);
extern int	is_valid(int table[4][4], int info[16], int depth);

void	print_table(int table[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			putchr(table[i][j] + '0');
			if (j == (4 - 1))
				putchr('\n');
			else
				putchr(' ');
			j++;
		}
		i++;
	}
}

int	find_case(int table[4][4], int info[16], int depth)
{
	int	row;
	int	col;
	int	i;

	if (depth == 16)
	{
		print_table(table);
		return (1);
	}
	row = depth / 4;
	col = depth % 4;
	i = 1;
	while (i <= 4)
	{
		table[row][col] = i;
		if (is_valid(table, info, depth))
		{
			if (find_case(table, info, depth + 1))
				return (1);
		}
		i++;
	}
	return (0);
}
