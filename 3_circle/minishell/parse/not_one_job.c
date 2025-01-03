/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_one_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:25:22 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:26:27 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	not_one_job(t_job **job, t_info *b_info, pid_t pid[])
{
	int		i;
	int		pipe;
	t_job	*temp;

	pipe = (*job)->pipe;
	temp = *job;
	while (temp != NULL)
	{
		exe_init_job(temp);
		if (execve_child(job, temp, b_info, pid))
			return ;
		temp = temp->next;
	}
	i = 0;
	while (i < pipe)
	{
		if (pid[i] != -1)
		{
			waitpid(pid[i], &g_status, 0);
			g_status = WEXITSTATUS(g_status);
			set_signal();
		}
		i++;
	}
}

int	execve_child(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[])
{
	if (!builtin_check(job) && find_list_key(b_info->env_list, "PATH") == 1)
		not_builtin_case(o_job, job, b_info, all_pid);
	else if (builtin_check(job))
	{
		builtin_case(o_job, job, b_info, all_pid);
	}
	else
		return (1);
	return (0);
}

void	not_builtin_case(t_job **o_job, t_job *job,
t_info *b_info, pid_t all_pid[])
{
	int		fd[2];
	pid_t	pid;
	char	*path;

	if (pipe(fd) == -1)
		return ;
	parent_signal();
	pid = fork();
	if (pid == -1)
		return ;
	all_pid[job->num - 1] = pid;
	(signal(SIGQUIT, sigquit_handle), signal(SIGINT, sigint_handle));
	if (pid == 0)
	{
		close(fd[0]);
		path = find_path(o_job, job, b_info, all_pid);
		about_job(job, fd);
		if (path == NULL)
			exit(127);
		execve(path, job->job, b_info->env_arr);
		free(path);
		path = NULL;
	}
	else
		(close(fd[1]), dup2(fd[0], STDIN_FILENO), close(fd[0]));
}

void	builtin_case(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[])
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;
	parent_signal();
	pid = fork();
	if (pid == -1)
		return ;
	all_pid[job->num - 1] = pid;
	(signal(SIGQUIT, sigquit_handle), signal(SIGINT, sigint_handle));
	if (pid == 0)
	{
		close(fd[0]);
		if (job->next)
			(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
		if (job->rd)
			set_in_out(job->in, job->out);
		ft_builtin(o_job, job, b_info, all_pid);
		exit(0);
	}
	else
		(close(fd[1]), dup2(fd[0], STDIN_FILENO), close(fd[0]));
}

void	about_job(t_job *job, int fd[])
{
	if (job->next)
		(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
	if (job->rd)
		set_in_out(job->in, job->out);
}
