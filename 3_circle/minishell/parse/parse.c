/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:27:04 by jacha             #+#    #+#             */
/*   Updated: 2025/01/01 17:12:57 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	parsing(t_job *jobs, t_info *b_info, char *cmd)
{
	t_commend	*com;
	t_pool		*pool;
	int			pipe;

	com = NULL;
	pool = NULL;
	if (ready_struct(&com, &pool))
		return (1);
	com->cmd = cmd;
	if (!com->cmd)
		free_error_1(jobs, b_info, com, pool);
	if (op_com(com, pool))
		return (0);
	init_all(com, pool);
	if (pipe_count_mal(com, pool) || add_cmd_pool(com, pool, b_info))
		return (1);
	pipe = pool->count + 1;
	init_pool(pool);
	pool_tokenizer(&jobs, pool);
	if (remove_quote(&jobs) || update_fd(&jobs, b_info))
		return (1);
	if (ft_strncmp("exit", jobs->job[0], 4) == 0 && jobs->next == NULL)
		ft_exit_2(b_info, jobs);
	execve_start(&jobs, b_info, pipe);
	return (0);
}

int	ready_struct(t_commend **com, t_pool **pool)
{
	*com = malloc(sizeof(t_commend));
	if (!*com)
	{
		return (1);
	}
	(*com)->cmd = NULL;
	*pool = malloc(sizeof(t_pool));
	if (!*pool)
	{
		free(*com);
		return (1);
	}
	(*pool)->cmd_pool = NULL;
	return (0);
}

void	free_error_1(t_job *jobs, t_info *b_info, t_commend *com, t_pool *pool)
{
	if (jobs != NULL)
		free_job(&jobs);
	free_all(com, pool);
	free_list(b_info->env_list);
	free_list(b_info->exp_list);
	free_split(b_info->env_arr);
	if (b_info->home != NULL)
		free(b_info->home);
	if (b_info->pwd != NULL)
		free(b_info->pwd);
	if (b_info->old_pwd != NULL)
		free(b_info->old_pwd);
	exit(0);
}

void	exit_valid_check(t_job *job)
{
	int	i;

	i = 0;
	while (job->job[i])
		i++;
	if (i > 2)
	{
		printf("exit\nbash: exit: too many arguments\n");
		return ;
	}
}

int	ft_exit_2(t_info *b_info, t_job *jobs)
{
	char	*num;

	num = "0";
	if (jobs->job[1] != NULL)
	{
		if (jobs->job[2] != NULL)
		{
			printf("bash: exit: too many arguments\n");
			num = ft_strdup("127");
			g_status = ft_atoi(num);
			free(num);
			return (1);
		}
		else if (ft_strcmp("exit", jobs->job[0]) == 0)
			num = ft_strdup(jobs->job[1]);
		else
			num = ft_strdup("127");
	}
	exit_free(b_info, jobs);
	g_status = ft_atoi(num);
	if (!num)
		free(num);
	exit(g_status);
}
