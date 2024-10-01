/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_op.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:20:13 by jacha             #+#    #+#             */
/*   Updated: 2024/06/24 16:27:50 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_list **a)
{
	t_list	*temp;
	t_list	*top;

	if (*a != NULL && (*a)->next != NULL)
	{
		top = (*a)->next;
		temp = last_point(*a);
		temp->next = *a;
		(*a)->next = NULL;
		*a = top;
	}
	ft_putstr_fd("ra\n", 1);
}

void	rb(t_list **b)
{
	t_list	*temp;
	t_list	*top;

	if (*b != NULL && (*b)->next != NULL)
	{
		top = (*b)->next;
		temp = last_point(*b);
		temp->next = *b;
		(*b)->next = NULL;
		*b = top;
	}
	ft_putstr_fd("rb\n", 1);
}

void	rr(t_list **a, t_list **b)
{
	ra(a);
	rb(b);
	ft_putstr_fd("rr\n", 1);
}
