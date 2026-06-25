/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:25:33 by jacha             #+#    #+#             */
/*   Updated: 2024/06/24 16:27:31 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra_o(t_list **a)
{
	t_list	*last;
	t_list	*semi_last;

	if (*a != NULL && (*a)->next != NULL)
	{
		if ((*a)->next->next != NULL)
		{
			last = last_point(*a);
			semi_last = semi_last_point(*a);
			last->next = *a;
			semi_last->next = NULL;
			*a = last;
		}
		else
		{
			last = *a;
			*a = last->next;
			(*a)->next = last;
			last->next = NULL;
		}
	}
}

void	rrb_o(t_list **b)
{
	t_list	*last;
	t_list	*semi_last;

	if (*b != NULL && (*b)->next != NULL)
	{
		if ((*b)->next->next != NULL)
		{
			last = last_point(*b);
			semi_last = semi_last_point(*b);
			last->next = *b;
			semi_last->next = NULL;
			*b = last;
		}
		else
		{
			last = *b;
			*b = last->next;
			(*b)->next = last;
			last->next = NULL;
		}
	}
}

void	rra(t_list **a)
{
	rra_o(a);
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_list **b)
{
	rrb_o(b);
	ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_list **a, t_list **b)
{
	rra(a);
	rrb(b);
	ft_putstr_fd("rrr\n", 1);
}
