/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 05:57:25 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 05:57:26 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	cd_valid_check(t_info *b_info)
{
	int	i;

	i = 0;
	while (b_info->cmd[i])
		i++;
	if (i > 2)
	{
		err_cd(b_info, 2);
		return (0);
	}
	if ((ft_strcmp(b_info->cmd[1], "--") == 0) && !b_info->cmd[2])
	{
		if (chdir(b_info->home) == 0)
			setting_pwd(b_info);
		return (0);
	}
	else if (ft_strcmp(b_info->cmd[1], "--") == 0)
	{
		if (chdir(b_info->cmd[2]) == 0)
			setting_pwd(b_info);
		return (0);
	}
	return (1);
}

char	*get_env_val(t_info *b_info, char *key)
{
	t_list	*current;
	char	*res;

	current = b_info->env_list;
	res = NULL;
	if (find_list_key(b_info->env_list, key) != 1)
		return (NULL);
	while (current != NULL)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			res = ft_strdup(current->val);
			break ;
		}
		current = current->next;
	}
	if (!current)
		return (NULL);
	return (res);
}

void	update_env_val(t_info *b_info, char *list_name, char *key, char *val)
{
	t_list	*current;

	if (ft_strcmp("exp", list_name) == 0)
		current = b_info->exp_list;
	else
		current = b_info->env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->val);
			current->val = NULL;
			current->val = ft_strdup(val);
			break ;
		}
		current = current->next;
	}
}

void	setting_pwd(t_info *b_info)
{
	b_info->flag = 1;
	if (b_info->old_pwd != NULL)
		free(b_info->old_pwd);
	b_info->old_pwd = ft_strdup(b_info->pwd);
	if (b_info->pwd != NULL)
		free(b_info->pwd);
	b_info->pwd = getcwd(NULL, 0);
	update_env_val(b_info, "exp", "OLDPWD", b_info->old_pwd);
	update_env_val(b_info, "env", "OLDPWD", b_info->old_pwd);
	update_env_val(b_info, "exp", "PWD", b_info->pwd);
	update_env_val(b_info, "env", "PWD", b_info->pwd);
}

int	run_cd(t_info *b_info)
{
	if (chdir(b_info->cmd[1]) != 0)
		err_cd(b_info, 3);
	setting_pwd(b_info);
	return (1);
}
