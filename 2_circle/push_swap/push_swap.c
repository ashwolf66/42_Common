/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:18:18 by jacha             #+#    #+#             */
/*   Updated: 2024/07/04 10:03:07 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	index_stack(t_list **a)
{
	t_list	*i;
	t_list	*j;

	i = *a;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (i->content > j->content)
				i->index++;
			else if (i->content < j->content)
				j->index++;
			else
				return (1);
			j = j->next;
		}
		i = i->next;
	}
	return (0);
}

int	int_check(char *argv)
{
	int	i;
	int	not_int;

	i = 0;
	not_int = 0;
	while (argv[i])
	{
		while (argv[i] == ' ')
			i++;
		if (argv[i] == '-' || argv[i] == '+')
			i++;
		if (argv[i] >= '0' && argv[i] <= '9')
		{
			not_int = 1;
			while (argv[i] >= '0' && argv[i] <= '9')
				i++;
		}
		else if (argv[i] != ' ')
			return (1);
		while (argv[i] == ' ')
			i++;
	}
	if (!not_int)
		return (1);
	return (0);
}

int	init_stack(t_list **a, int argc, char **argv)
{
	int		i;
	int		j;
	char	**ch;

	i = 1;
	while (i < argc)
	{
		if (int_check(argv[i]) == 1)
			return (1);
		ch = ft_split(argv[i], ' ');
		j = 0;
		while (ch[j])
		{
			if ((len_check(ch[j]) == 1 && zero_check(ch[j]) == 1) ||  \
					ft_atoi(ch[j]) != ft_atol(ch[j]))
			{
				free_mem(ch);
				return (1);
			}
			ft_lstadd_back(a, ft_lstnew(ft_atoi(ch[j++])));
		}
		free_mem(ch);
		i++;
	}
	return (0);
}

int	sort_select(t_list **a, t_list **b)
{
	int	i;

	i = ft_lstsize(*a);
	if (is_sorted(a))
	{
		free_stack(a);
		free_stack(b);
		return (0);
	}
	if (i <= 5)
		simple_sort(a, b);
	else
		radix_sort(a, b);
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	a = NULL;
	b = NULL;
	if (argc > 1)
	{
		if (init_stack(&a, argc, argv) == 1)
		{
			ft_putstr_fd("Error\n", 2);
			free_stack(&a);
			return (0);
		}
		if (index_stack(&a) == 1)
		{
			ft_putstr_fd("Error\n", 2);
			free_stack(&a);
			return (0);
		}
		sort_select(&a, &b);
		free_stack(&a);
		free_stack(&b);
	}
	return (0);
}
