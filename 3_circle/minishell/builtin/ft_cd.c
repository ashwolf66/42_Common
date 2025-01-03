/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:13:16 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 04:13:17 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	ft_cd(t_info *b_info)
{
	if (!b_info->cmd[1])
	{
		if (ft_strcmp(b_info->cmd[0], "cd") == 0)
		{
			if (find_list_key(b_info->env_list, "HOME") != 1)
				print_err("bash: cd: HOME not set\n", "");
			else
				chdir(b_info->home);
			setting_pwd(b_info);
			return (1);
		}
		else
		{
			print_err("cd input error\n", "");
			return (1);
		}
	}
	if (cd_valid_check(b_info) != 1)
		return (1);
	if (type_check(b_info) == 1)
		return (1);
	if (run_cd(b_info) == 1)
		return (1);
	return (1);
}

int	type_check(t_info *b_info)
{
	if (b_info->cmd[1][0] == '~')
	{
		type_tilde(b_info);
		return (1);
	}
	else if (b_info->cmd[1][0] == '-')
	{
		type_dash(b_info);
		return (1);
	}
	return (0);
}

int	type_tilde(t_info *b_info)
{
	char	*temp;

	temp = get_env_val(b_info, "HOME");
	if (find_list_key(b_info->env_list, "HOME") == 1)
		chdir(temp);
	else
		chdir(b_info->home);
	free(temp);
	if (b_info->cmd[1][1] == '/')
		setting_pwd(b_info);
	else
		setting_pwd(b_info);
	return (1);
}

int	type_dash(t_info *b_info)
{
	if (find_list_key(b_info->env_list, "OLDPWD") != 1)
	{
		print_err("bash: cd: OLDPWD not set\n", "");
		return (1);
	}
	else if (!b_info->cmd[1][1])
	{
		if (chdir(b_info->old_pwd) == 0)
			printf("%s\n", b_info->old_pwd);
		else
		{
			err_cd(b_info, 3);
			setting_pwd(b_info);
			return (1);
		}
		setting_pwd(b_info);
	}
	return (1);
}
