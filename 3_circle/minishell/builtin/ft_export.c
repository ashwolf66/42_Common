/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:11:47 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 04:11:49 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	ft_export(t_info *b_info)
{
	char	**key_val;
	int		i;

	key_val = NULL;
	i = 0;
	if (!b_info->cmd[1])
	{
		print_list(b_info->exp_list, "exp");
		return (1);
	}
	while (b_info->cmd[++i])
	{
		if (!exp_valid_check(b_info, i))
			err_exp(b_info, 1);
		else
		{
			key_val = key_val_separ(b_info->cmd[i]);
			add_union(b_info, key_val, i);
			free_split(key_val);
		}
	}
	return (1);
}

void	add_union(t_info *b_info, char **key_val, int i)
{
	int	flag;

	flag = find_list_key(b_info->exp_list, key_val[0]);
	if (equal_and_plue_search(b_info->cmd[i]) == 2)
		plus_case(b_info, key_val, flag, i);
	else if (equal_and_plue_search(b_info->cmd[i]) == 1)
		equal_case(b_info, key_val, flag, i);
	else
		nothing_case(b_info, flag, i);
}

void	plus_case(t_info *b_info, char **key_val, int flag, int i)
{
	if (flag == 1)
	{
		plus_util(b_info->env_list, key_val);
		plus_util(b_info->exp_list, key_val);
	}
	else
	{
		add_sorted_node(&b_info->env_list, b_info->cmd[i]);
		add_sorted_node(&b_info->exp_list, b_info->cmd[i]);
	}
}

void	equal_case(t_info *b_info, char **key_val, int flag, int i)
{
	if (flag == 1)
	{
		equal_util(b_info->env_list, key_val);
		equal_util(b_info->exp_list, key_val);
	}
	else
	{
		add_sorted_node(&b_info->env_list, b_info->cmd[i]);
		add_sorted_node(&b_info->exp_list, b_info->cmd[i]);
	}
}

void	nothing_case(t_info *b_info, int flag, int i)
{
	if (flag == 1)
		return ;
	else
	{
		add_sorted_node(&b_info->env_list, b_info->cmd[i]);
		add_sorted_node(&b_info->exp_list, b_info->cmd[i]);
	}
}
