/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:14:11 by jacha             #+#    #+#             */
/*   Updated: 2025/01/01 19:23:48 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	ft_env(t_info *b_info)
{
	if (b_info->cmd[1] == NULL && ft_strcmp("env", b_info->cmd[0]) == 0)
	{
		if (find_list_key(b_info->env_list, "PATH") == 1)
		{
			sort_env(b_info->env_list);
			print_list(b_info->env_list, "env");
		}
		else
			err_env(1);
	}
	else if (ft_strcmp("env", b_info->cmd[0]) == 0)
		printf("env: ‘%s’: No such file or directory\n", b_info->cmd[1]);
	else
		printf("bash: command not found: %s\n", b_info->cmd[0]);
	return (1);
}
