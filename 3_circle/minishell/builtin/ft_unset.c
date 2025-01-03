/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:02:58 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 04:02:59 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	ft_unset(t_info *b_info)
{
	int	i;

	i = 0;
	if (ft_strcmp("unset", b_info->cmd[0]) == 0)
	{
		while (b_info->cmd[++i])
		{
			if (find_list_key(b_info->env_list, b_info->cmd[i]) == 1)
				del_node(&b_info->env_list, b_info->cmd[i]);
			if (find_list_key(b_info->exp_list, b_info->cmd[i]) == 1)
				del_node(&b_info->exp_list, b_info->cmd[i]);
		}
		return (1);
	}
	else
		printf("%s: command not found\n", b_info->cmd[0]);
	return (1);
}
