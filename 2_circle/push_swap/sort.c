/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:32:45 by jacha             #+#    #+#             */
/*   Updated: 2024/06/27 11:53:45 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_max_bits(t_list *a)
{
	int		max;
	int		max_bits;
	t_list	*temp;

	max = 0;
	max_bits = 0;
	temp = a;
	while (temp)
	{
		if (temp->index > max)
			max = temp->index;
		temp = temp->next;
	}
	while ((max >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

void	radix_a(t_list **a, t_list **b, int i)
{
	if ((((*a)->index >> i) & 1) == 1)
		ra(a);
	else
		pb(b, a);
}

void	radix_sort(t_list **a, t_list **b)
{
	int	max_bits;
	int	i;
	int	j;
	int	size;

	i = 0;
	max_bits = get_max_bits(*a);
	while (i < max_bits)
	{
		j = 0;
		size = ft_lstsize(*a);
		while (j < size)
		{
			radix_a(a, b, i);
			j++;
		}
		j = ft_lstsize(*b);
		while (j-- > 0)
			pa(a, b);
		i++;
	}
}

int	len_check(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 11)
		return (1);
	return (0);
}
