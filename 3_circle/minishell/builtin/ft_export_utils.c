/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:14:56 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 04:14:57 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	exp_valid_check(t_info *b_info, int index)
{
	if (check_key_format(b_info->cmd[index]) == 1)
		return (1);
	else if (check_key_format(b_info->cmd[index]) == 2)
	{
		write(1, "NULL\n", 5);
		return (1);
	}
	else if (check_key_format(b_info->cmd[index]) == 0)
		return (0);
	return (0);
}

int	check_key_format(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (2);
	if (!((key[i] >= 'a' && key[i] <= 'z')
			|| (key[i] >= 'A' && key[i] <= 'Z')
			|| (key[i] == '_')))
		return (0);
	while (key[i] && key[i] != '+' && key[i] != '=')
	{
		if (!((key[i] >= 'a' && key[i] <= 'z')
				|| (key[i] >= 'A' && key[i] <= 'Z')
				|| (key[i] >= '1' && key[i] <= '9')
				|| key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	equal_and_plue_search(char *cmd)
{
	int	locate;

	locate = 0;
	if (!cmd || !cmd[locate])
		return (0);
	while (cmd[locate])
	{
		if (cmd[locate] == '+' && cmd[locate + 1] == '=')
			return (2);
		if (cmd[locate] == '=')
			return (1);
		locate++;
	}
	return (0);
}

void	plus_util(t_list *list_name, char **key_val)
{
	t_list	*current;
	char	*temp;

	current = list_name;
	while (current)
	{
		if (ft_strcmp(current->key, key_val[0]) == 0)
		{
			if (key_val[1])
			{
				if (!current->val)
					temp = ft_strdup("");
				else
					temp = current->val;
				current->val = ft_strjoin(temp, key_val[1]);
				free(temp);
			}
			else
				current->val = ft_strdup(key_val[1]);
			break ;
		}
		current = current->next;
	}
}

void	equal_util(t_list *list_name, char **key_val)
{
	t_list	*current;

	current = list_name;
	while (current)
	{
		if (ft_strcmp(current->key, key_val[0]) == 0)
		{
			free(current->val);
			current->val = NULL;
			if (key_val[1])
				current->val = ft_strdup(key_val[1]);
			else
				current->val = NULL;
			break ;
		}
		current = current->next;
	}
}
