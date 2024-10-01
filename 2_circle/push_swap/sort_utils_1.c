/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logname <logname@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 02:14:44 by logname           #+#    #+#             */
/*   Updated: 2024/06/27 11:59:20 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min(t_list **a, int val)
{
	t_list	*top;
	int		min;

	top = *a;
	min = top->index;
	while (top->next)
	{
		top = top->next;
		if ((top->index < min) && top->index != val)
			min = top->index;
	}
	return (min);
}

void	sort_3(t_list **a)
{
	int	max;

	max = get_max(a);
	if ((*a)->index == max)
		ra(a);
	if ((*a)->next->index == max)
		rra(a);
	if ((*a)->index > (*a)->next->index)
		sa(a);
}

void	sort_4(t_list **a, t_list **b)
{
	int	distance;

	if (is_sorted(a))
		return ;
	distance = get_distance(a, get_min(a, -1));
	if (distance == 1)
		ra(a);
	else if (distance == 2)
	{
		ra(a);
		ra(a);
	}
	else if (distance == 3)
		rra(a);
	if (is_sorted(a))
		return ;
	pb(b, a);
	sort_3(a);
	pa(a, b);
}

void	sort_5(t_list **a, t_list **b)
{
	int	distance;

	distance = get_distance(a, get_min(a, -1));
	if (distance == 1)
		ra(a);
	else if (distance == 2)
	{
		ra(a);
		ra(a);
	}
	else if (distance == 3)
	{
		rra(a);
		rra(a);
	}
	else if (distance == 4)
		rra(a);
	if (is_sorted(a))
		return ;
	pb(b, a);
	sort_4(a, b);
	pa(a, b);
}

void	simple_sort(t_list **a, t_list **b)
{
	int	size;

	if (is_sorted(a) || ft_lstsize(*a) == 0 \
			|| ft_lstsize(*a) == 1)
		return ;
	size = ft_lstsize(*a);
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_3(a);
	else if (size == 4)
		sort_4(a, b);
	else if (size == 5)
		sort_5(a, b);
}
