/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 03:56:30 by jacha             #+#    #+#             */
/*   Updated: 2025/01/01 16:35:20 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	env_init(t_info *b_info, char **env)
{
	b_info->env_list = NULL;
	b_info->exp_list = NULL;
	b_info->cmd = NULL;
	b_info->flag = 0;
	b_info->end_stat = 0;
	make_list(env, &b_info->env_list);
	make_list(env, &b_info->exp_list);
	sort_env(b_info->env_list);
	sort_exp(b_info->exp_list);
	del_node(&b_info->exp_list, "_");
	b_info->env_arr = update_env_arr(env);
	b_info->home = get_env_val(b_info, "HOME");
	b_info->old_pwd = get_env_val(b_info, "OLDPWD");
	b_info->pwd = get_env_val(b_info, "PWD");
}

char	**update_env_arr(char **env)
{
	char	**res;
	int		env_len;
	int		i;

	env_len = 0;
	i = -1;
	while (env[env_len])
		env_len++;
	res = malloc(sizeof(char *) * (env_len + 1));
	if (!res)
		return (NULL);
	while (++i < env_len)
		res[i] = ft_strdup(env[i]);
	res[i] = NULL;
	return (res);
}

void	list_val_swap(t_list *current, t_list *temp)
{
	char	*temp_key;
	char	*temp_val;

	temp_key = current->key;
	temp_val = current->val;
	current->key = temp->key;
	current->val = temp->val;
	temp->key = temp_key;
	temp->val = temp_val;
}

void	sort_env(t_list *head)
{
	t_list	*current;
	t_list	*target;
	t_list	*prev;

	current = head;
	target = head;
	prev = NULL;
	while (target != NULL)
	{
		if (ft_strcmp("_", target->key) == 0)
			break ;
		prev = target;
		target = target->next;
	}
	if (target == NULL || target->next == NULL)
		return ;
	if (prev != NULL)
		prev->next = target->next;
	else
		head = target->next;
	while (current->next != NULL)
		current = current->next;
	current->next = target;
	target->next = NULL;
}

void	sort_exp(t_list *head)
{
	t_list	*current;
	t_list	*temp;

	current = head;
	while (current != NULL)
	{
		temp = current->next;
		while (temp != NULL)
		{
			if (ft_strcmp(current->key, temp->key) > 0)
				list_val_swap(current, temp);
			temp = temp->next;
		}
		current = current->next;
	}
}
