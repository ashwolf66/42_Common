/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   count_view.c                                       :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: yonan <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/01/23 18:27:51 by yonan	       #+#    #+#	      */
/*   Updated: 2024/01/23 18:31:06 by yonan            ###   ########.fr       */
/*									      */
/* ************************************************************************** */

int	cnt_up_view(int table[4][4], int col)
{
	int	i;
	int	cnt_u;
	int	max_u;

	cnt_u = 0;
	max_u = 0;
	i = 0;
	while (i < 4)
	{
		if (max_u < table[i][col])
		{
			max_u = table[i][col];
			cnt_u++;
		}
		i++;
	}
	return (cnt_u);
}

int	cnt_down_view(int table[4][4], int col)
{
	int	i;
	int	cnt_d;
	int	max_d;

	cnt_d = 0;
	max_d = 0;
	i = 4 - 1;
	while (i >= 0)
	{
		if (max_d < table[i][col])
		{
			max_d = table[i][col];
			cnt_d++;
		}
		i--;
	}
	return (cnt_d);
}

int	cnt_left_view(int table[4][4], int row)
{
	int	i;
	int	cnt_l;
	int	max_l;

	cnt_l = 0;
	max_l = 0;
	i = 0;
	while (i < 4)
	{
		if (max_l < table[row][i])
		{
			max_l = table[row][i];
			cnt_l++;
		}
		i++;
	}
	return (cnt_l);
}

int	cnt_right_view(int table[4][4], int row)
{
	int	i;
	int	cnt_r;
	int	max_r;

	cnt_r = 0;
	max_r = 0;
	i = 4 - 1;
	while (i >= 0)
	{
		if (max_r < table[row][i])
		{
			max_r = table[row][i];
			cnt_r++;
		}
		i--;
	}
	return (cnt_r);
}
