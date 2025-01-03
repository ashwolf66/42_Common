/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:00:32 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 04:00:34 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	make_list(char **val, t_list **linked_list)
{
	int	i;

	i = -1;
	while (val[++i])
		add_back_node(linked_list, val[i]);
}

t_list	*create_node(char *key_val)
{
	t_list	*new_node;
	char	**sp_env;

	sp_env = key_val_separ(key_val);
	new_node = (t_list *)malloc(sizeof(t_list));
	new_node->key = ft_strdup(sp_env[0]);
	new_node->val = exp_val(&sp_env[1]);
	new_node->next = NULL;
	free_split(sp_env);
	return (new_node);
}

void	add_sorted_node(t_list **head, char *key_val)
{
	t_list	*new_node;
	t_list	*current;

	new_node = create_node(key_val);
	if (*head == NULL || ft_strcmp(new_node->key, (*head)->key) < 0)
	{
		new_node->next = *head;
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next && ft_strcmp(new_node->key, current->next->key) > 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
}

void	add_back_node(t_list **head, char *val)
{
	t_list	*new_node;
	t_list	*current;

	new_node = create_node(val);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	del_node(t_list **head, char *key)
{
	t_list	*current;
	t_list	*prev;

	if (!key)
		return ;
	current = *head;
	prev = NULL;
	while (current->next != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			break ;
		prev = current;
		current = current->next;
	}
	if (current->key != NULL)
		free(current->key);
	if (current->val != NULL)
		free(current->val);
	if (prev != NULL)
		prev->next = current->next;
	if (current != NULL)
		free(current);
}
