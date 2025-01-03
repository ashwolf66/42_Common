/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:37:02 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:37:28 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	execve_start(t_job **job, t_info *b_info, int pipe)
{
	int		in;
	int		out;
	pid_t	*pid;

	(*job)->pipe = 0;
	(*job)->pipe = pipe;
	pid = malloc(sizeof(pid_t) * (*job)->pipe);
	if (!pid)
	{
		free_parse(job, &b_info);
		return ;
	}
	start_exe(&in, &out);
	if ((*job)->pipe == 1 && builtin_check(*job))
		one_job(job, *job, b_info, pid);
	else
		not_one_job(job, b_info, pid);
	end_exe(&in, &out);
	free_mem(b_info->cmd);
	b_info->cmd = NULL;
	free_job(job);
	free(pid);
}

void	start_exe(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

void	end_exe(int *in, int *out)
{
	dup2(*in, STDIN_FILENO);
	dup2(*out, STDOUT_FILENO);
	close(*in);
	close(*out);
}

int	builtin_check(t_job *jobs)
{
	if (ft_strncmp("cd", jobs->job[0], 2) == 0)
		return (1);
	else if (ft_strncmp("echo", jobs->job[0], 4) == 0)
		return (1);
	else if (ft_strncmp("env", jobs->job[0], 3) == 0)
		return (1);
	else if (ft_strncmp("exit", jobs->job[0], 4) == 0)
		return (1);
	else if (ft_strncmp("export", jobs->job[0], 6) == 0)
		return (1);
	else if (ft_strncmp("pwd", jobs->job[0], 3) == 0)
		return (1);
	else if (ft_strncmp("unset", jobs->job[0], 5) == 0)
		return (1);
	else
		return (0);
}
