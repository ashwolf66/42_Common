/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:14:35 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 04:14:36 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	ft_exit(t_info *b_info)
{
	printf("exit\n");
	all_free(b_info);
	return (1);
}

int	is_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (VAL_ERR);
	}
	return (1);
}

void	all_free(t_info *b_info)
{
	free_split(b_info->cmd);
	free_list(b_info->env_list);
	free_list(b_info->exp_list);
	if (b_info->home != NULL)
		free(b_info->home);
	if (b_info->pwd != NULL)
		free(b_info->pwd);
	if (b_info->old_pwd != NULL)
		free(b_info->old_pwd);
}
