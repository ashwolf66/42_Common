/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:54:16 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 09:44:33 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	g_status = 0;

int	main(int ac, char **av, char **env)
{
	t_info		b_info;
	t_job		*jobs;
	char		*cmd;

	(void)ac;
	(void)av;
	if (ac != 1)
		return (0);
	env_init(&b_info, env);
	(signal(SIGINT, signal_handle), signal(SIGQUIT, SIG_IGN));
	while (1)
	{
		cmd = readline("minishell > ");
		if (ft_strlen(cmd) > 0 && check_str(cmd))
		{
			free(cmd);
			continue ;
		}
		add_history(cmd);
		jobs = NULL;
		parsing(jobs, &b_info, cmd);
	}
	return (0);
}

int	ft_builtin(t_job **o_job, t_job *jobs, t_info *b_info, pid_t all_pid[])
{
	(void) all_pid;
	(void) o_job;
	b_info->cmd = ms_strdup(jobs->job);
	if (!b_info->cmd)
		return (1);
	if (ft_strncmp("cd", jobs->job[0], 2) == 0)
		return (ft_cd(b_info));
	else if (ft_strncmp("echo", jobs->job[0], 4) == 0)
		return (ft_echo(b_info));
	else if (ft_strncmp("env", jobs->job[0], 3) == 0)
		return (ft_env(b_info));
	else if (ft_strncmp("exit", jobs->job[0], 4) == 0)
		return (ft_exit_2(b_info, jobs));
	else if (ft_strncmp("export", jobs->job[0], 6) == 0)
		return (ft_export(b_info));
	else if (ft_strncmp("pwd", jobs->job[0], 3) == 0)
		return (ft_pwd(b_info));
	else if (ft_strncmp("unset", jobs->job[0], 5) == 0)
		return (ft_unset(b_info));
	else
		return (-1);
}

int	check_str(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ' && (cmd[i] < 9 || cmd[i] > 13))
			return (0);
		i++;
	}
	return (1);
}
