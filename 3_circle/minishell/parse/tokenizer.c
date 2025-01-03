/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:22:05 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:22:17 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	pool_tokenizer(t_job **job, t_pool *pool)
{
	if (!pool->cmd_pool[pool->r_indx])
	{
		init_pool(pool);
		free_mem(pool->cmd_pool);
		pool->cmd_pool = NULL;
		free(pool);
		pool = NULL;
		return ;
	}
	make_job_col(job, pool);
	pool->r_indx++;
	pool->indx = 0;
	pool_tokenizer(job, pool);
}

void	make_job_col(t_job **job, t_pool *pool)
{
	ms_lstadd_back(job, ms_lstnew(ms_split(pool, ' '), pool->r_indx + 1));
}
