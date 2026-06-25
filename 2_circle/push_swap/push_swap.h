/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:19:54 by jacha             #+#    #+#             */
/*   Updated: 2024/06/27 11:51:58 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		init_stack(t_list **a, int argc, char **argv);
int		int_check(char *argv);
int		index_stack(t_list **a);
int		get_max_bits(t_list *a);
int		is_sorted(t_list **a);
int		get_distance(t_list **a, int index);
int		get_max(t_list **a);
int		sort_select(t_list **a, t_list **b);
int		len_check(char *argv);
int		zero_check(char *argv);
void	pa(t_list **a, t_list **b);
void	pb(t_list **b, t_list **a);
void	sa(t_list **a);
void	sb(t_list **b);
void	ss(t_list **a, t_list **b);
void	ra_o(t_list **a);
void	rb_o(t_list **b);
void	ra(t_list **a);
void	rb(t_list **b);
void	rr(t_list **a, t_list **b);
void	rra_o(t_list **a);
void	rrb_o(t_list **b);
void	rra(t_list **a);
void	rrb(t_list **b);
void	rrr(t_list **a, t_list **b);
void	radix_sort(t_list **a, t_list **b);
void	radix_a(t_list **a, t_list **b, int i);
void	simple_sort(t_list **a, t_list **b);
void	free_mem(char **temp);
void	free_stack(t_list **stack);
t_list	*last_point(t_list *t);
t_list	*semi_last_point(t_list *t);

#endif
