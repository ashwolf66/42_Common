/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:39:23 by jacha             #+#    #+#             */
/*   Updated: 2024/06/29 13:14:57 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_mem(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
		free(temp[i++]);
	free(temp);
}

void	free_stack(t_list **stack)
{
	t_list	*temp;

	while (stack && *stack)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
}

int	zero_check(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] != '0')
			return (1);
		i++;
	}
	return (0);
}
