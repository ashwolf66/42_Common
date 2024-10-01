/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: jacha <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/01/23 17:02:38 by jacha	       #+#    #+#	      */
/*   Updated: 2024/01/23 18:26:49 by yonan            ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include <unistd.h>

extern int	cnt_up_view(int table[4][4], int col);
extern int	cnt_down_view(int table[4][4], int col);
extern int	cnt_left_view(int table[4][4], int row);
extern int	cnt_right_view(int table[4][4], int row);

int	is_valid_col(int table[4][4], int info[16], int col)
{
	int	cnt_u;
	int	cnt_d;

	cnt_u = cnt_up_view(table, col);
	cnt_d = cnt_down_view(table, col);
	if (info[4 * 0 + col] == cnt_u && info[4 * 1 + col] == cnt_d)
		return (1);
	return (0);
}

int	is_valid_row(int table[4][4], int info[16], int row)
{
	int	cnt_l;
	int	cnt_r;

	cnt_l = cnt_left_view(table, row);
	cnt_r = cnt_right_view(table, row);
	if (info[4 * 2 + row] == cnt_l && info[4 * 3 + row] == cnt_r)
		return (1);
	return (0);
}

int	is_valid(int table[4][4], int info[16], int depth)
{
	int	row;
	int	col;
	int	i;

	row = depth / 4;
	col = depth % 4;
	i = 0;
	while (i < col)
	{
		if (table[row][i] == table[row][col])
			return (0);
		i++;
	}
	i = 0;
	while (i < row)
	{
		if (table[i][col] == table[row][col])
			return (0);
		i++;
	}
	if (col == (4 - 1) && !is_valid_row(table, info, row))
		return (0);
	if (row == (4 - 1) && !is_valid_col(table, info, col))
		return (0);
	return (1);
}
