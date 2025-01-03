/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dr_case.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:39:50 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:41:19 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	l_dr_case(int l_d, t_job *job, t_info *b_info)
{
	if (l_d == 1)
		job->in = open(job->job[job->r_indx], O_RDONLY);
	else if (l_d == 2)
		heredoc_case(job, b_info);
}

void	r_dr_case(int r_d, t_job *job)
{
	if (r_d == 1)
		job->out = open(job->job[job->r_indx],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (r_d == 2)
		job->out = open(job->job[job->r_indx],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
}

void	heredoc_case(t_job *job, t_info *b_info)
{
	char	*name;

	name = job->job[job->r_indx];
	if (heredoc_start(name, b_info))
		return ;
	job->in = open(".hd_temp_file", O_RDONLY);
}

int	heredoc_start(char *name, t_info *b_info)
{
	pid_t	pid;

	pid = fork();
	parent_signal();
	if (pid == 0)
	{
		heredoc_signal();
		if (create_temp_file(name, b_info))
			exit(1);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		set_signal();
		if (g_status >> 8 == 130)
			return (1);
		return (0);
	}
}

int	create_temp_file(char *name, t_info *b_info)
{
	int		fd;
	char	*str;
	char	*temp;

	fd = open(".hd_temp_file",
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (1);
	while (1)
	{
		str = readline("> ");
		if (ft_strchr(str, '$') != 0)
		{
			temp = find_env(str, b_info);
			free(str);
			str = temp;
		}
		if (end_check(name, str, ft_strlen(str)))
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	close(fd);
	return (0);
}
