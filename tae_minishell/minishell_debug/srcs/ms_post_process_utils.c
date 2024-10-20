/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_post_process_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:18:40 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 11:19:11 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	_post_process_check_builtin(t_job *job)
{
	size_t		idx;
	const char	*builtin_list[] = {
		"echo", "cd", "pwd", "export", "unser", "env", "exit", NULL};

	idx = 0;
	while (builtin_list[idx] != NULL)
	{
		if (ms_strcmp(builtin_list[idx], job->cmd) == 0)
		{
			return (true);
		}
		++idx;
	}
	return (false);
}

int	_check_path_dir(t_job *job)
{
	if (job->cmd == NULL)
	{
		return (NONE);
	}
	else if (!ms_strncmp(job->cmd, "./", 2) || !ms_strncmp(job->cmd, "../", 3))
	{
		return (RELATIVE_PATH);
	}
	else if (!ms_strncmp(job->cmd, "/", 1))
	{
		return (ABSOLUTE_PATH);
	}
	else
	{
		return (PURE_PATH);
	}
}

void	_post_process_print_err(const char *str)
{
	int	stdout_fd;

	stdout_fd = dup(1);
	dup2(2, 1);
	printf("minishell: '%s' command not found\n", str);
	dup2(stdout_fd, 1);
	close(stdout_fd);
}

int	_post_process_join_path(t_job *job, t_vector *path)
{
	int		idx;
	char	*cmd;

	idx = -1;
	if (_post_process_check_builtin(job))
	{
		job->is_builtin = true;
		return (true);
	}
	while (++idx < (int)path->size)
	{
		cmd = ms_strjoin("/", ms_strdup(job->cmd));
		cmd = ms_strjoin(ms_vector_get(path, idx), cmd);
		if (access(cmd, X_OK) == 0)
		{
			job->cmd = cmd;
			return (true);
		}
	}
	if (idx >= (int)path->size)
	{
		_post_process_print_err(job->cmd);
		return (false);
	}
	return (true);
}
