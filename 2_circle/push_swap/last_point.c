/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:39:28 by jacha             #+#    #+#             */
/*   Updated: 2024/06/27 11:51:24 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*last_point(t_list	*t)
{
	t_list	*temp;

	temp = t;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

t_list	*semi_last_point(t_list *t)
{
	t_list	*temp;

	temp = t;
	while (temp->next->next != NULL)
		temp = temp->next;
	return (temp);
}

int	is_sorted(t_list **a)
{
	t_list	*top;

	top = *a;
	while (top && top->next)
	{
		if (top->content > top->next->content)
			return (0);
		top = top->next;
	}
	return (1);
}

int	get_distance(t_list **a, int index)
{
	t_list	*top;
	int		distance;

	distance = 0;
	top = *a;
	while (top)
	{
		if (top->index == index)
			break ;
		distance++;
		top = top->next;
	}
	return (distance);
}

int	get_max(t_list **a)
{
	t_list	*top;
	int		max;

	top = *a;
	max = top->index;
	while (top->next)
	{
		top = top->next;
		if (top->index > max)
			max = top->index;
	}
	return (max);
}
