/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 09:03:31 by jacha             #+#    #+#             */
/*   Updated: 2025/01/01 16:36:13 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	exit_free(t_info *b_info, t_job *jobs)
{
	if (jobs != NULL)
		free_job(&jobs);
	free_list(b_info->env_list);
	free_list(b_info->exp_list);
	free_split(b_info->env_arr);
	if (b_info->home != NULL)
		free(b_info->home);
	if (b_info->pwd != NULL)
		free(b_info->pwd);
	if (b_info->old_pwd != NULL)
		free(b_info->old_pwd);
}

int	op_com(t_commend *com, t_pool *pool)
{
	if (com->cmd[0] == '\0')
	{
		free_all(com, pool);
		return (1);
	}
	init_commend(com);
	if (syntax_check(com))
	{
		syntax_error(com, pool);
		return (1);
	}
	return (0);
}
