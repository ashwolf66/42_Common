/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_op.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:24:34 by jacha             #+#    #+#             */
/*   Updated: 2024/06/17 16:38:44 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **a)
{
	t_list	*temp;

	if (*a != NULL && (*a)->next != NULL)
	{
		temp = (*a)->next;
		(*a)->next = temp->next;
		temp->next = *a;
		*a = temp;
	}
	ft_putstr_fd("sa\n", 1);
}

void	sb(t_list **b)
{
	t_list	*temp;

	if (*b != NULL && (*b)->next != NULL)
	{
		temp = (*b)->next;
		(*b)->next = temp->next;
		temp->next = *b;
		*b = temp;
	}
	ft_putstr_fd("sb\n", 1);
}

void	ss(t_list **a, t_list **b)
{
	sa(a);
	sb(b);
	ft_putstr_fd("ss\n", 1);
}
