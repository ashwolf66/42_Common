/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:35:25 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:35:54 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	free_mem(char **temp)
{
	int	i;

	if (!temp || !*temp)
		return ;
	i = 0;
	while (temp[i])
	{
		if (temp[i])
		{
			free(temp[i]);
			temp[i] = NULL;
		}
		i++;
	}
	free(temp);
	temp = NULL;
}

void	free_job(t_job **job)
{
	t_job	*temp;

	if (!job || !*job)
		return ;
	while (*job)
	{
		temp = (*job)->next;
		if ((*job)->job)
		{
			free_mem((*job)->job);
			(*job)->job = NULL;
		}
		free(*job);
		*job = temp;
	}
	*job = NULL;
}

void	free_parse(t_job **job, t_info **b_info)
{
	if (b_info && *b_info)
	{
		if ((*b_info)->cmd)
		{
			free_mem((*b_info)->cmd);
			(*b_info)->cmd = NULL;
		}
	}
	free_job(job);
}

void	free_all(t_commend *com, t_pool *pool)
{
	if (pool->cmd_pool != NULL)
	{
		free_mem(pool->cmd_pool);
		pool->cmd_pool = NULL;
	}
	free(pool);
	if (com->cmd != NULL)
	{
		free(com->cmd);
		com->cmd = NULL;
	}
	free(com);
}
