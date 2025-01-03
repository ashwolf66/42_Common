/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:36:18 by jacha             #+#    #+#             */
/*   Updated: 2025/01/01 16:57:57 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

char	*find_path(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[])
{
	t_list	*env_list;
	char	**paths;
	char	*path;
	char	*str;
	int		i;

	i = 0;
	env_list = find_exe(o_job, job, b_info, all_pid);
	paths = ft_split(env_list->val, ':');
	while (paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		path = ft_strjoin(str, job->job[0]);
		free(str);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	free_mem(paths);
	paths = NULL;
	if (access(job->job[0], F_OK) == 0 && access(job->job[0], X_OK) == 0)
		return (job->job[0]);
	(not_cmd(o_job, job, b_info, all_pid), exit(127));
}

t_list	*find_exe(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[])
{
	t_list	*temp;
	DIR		*dir;

	dir = opendir(job->job[0]);
	if (dir)
	{
		write(2, "minishell > ", ft_strlen("minishell > "));
		write(2, job->job[0], ft_strlen(job->job[0]));
		write(2, ": is directory\n", ft_strlen(": is directory\n"));
		closedir(dir);
		free_op(o_job, job, b_info, all_pid);
		exit(126);
	}
	temp = b_info->env_list;
	while (temp)
	{
		if (ft_strncmp(temp->key, "PATH", 4) == 0)
			return (temp);
		temp = temp->next;
	}
	return (0);
}

void	free_op(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[])
{
	free_mem(b_info->cmd);
	free_list(b_info->env_list);
	free_list(b_info->exp_list);
	free_split(b_info->env_arr);
	if (b_info->home != NULL)
		free(b_info->home);
	if (b_info->pwd != NULL)
		free(b_info->pwd);
	if (b_info->old_pwd != NULL)
		free(b_info->old_pwd);
	free_job(&job);
	free_job(o_job);
	job = NULL;
	free(all_pid);
}

void	not_cmd(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[])
{
	write(2, job->job[0], ft_strlen(job->job[0]));
	write(2, ": command not found\n",
		ft_strlen(": command not found\n"));
	free_op(o_job, job, b_info, all_pid);
}
