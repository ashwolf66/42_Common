/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:34:47 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:35:11 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	init_all(t_commend *com, t_pool *pool)
{
	init_commend(com);
	init_pool(pool);
}

void	init_commend(t_commend *com)
{
	com->temp_len = 0;
	com->size = 0;
	com->indx = 0;
	com->indx_start = 0;
	com->s_quote = 0;
	com->d_quote = 0;
	com->pipe = 1;
	com->pipe_count = 0;
	com->count = 0;
	com->l_direct = 0;
	com->r_direct = 0;
	com->l_count = 0;
	com->r_count = 0;
	com->di_space = 0;
	com->len = 0;
}

void	init_pool(t_pool *pool)
{
	pool->indx = 0;
	pool->r_indx = 0;
	pool->s_quote = 0;
	pool->d_quote = 0;
	pool->s_count = 0;
	pool->count_temp = 0;
	pool->count = 0;
}

void	init_pool_quote(t_pool *pool)
{
	pool->s_quote = 0;
	pool->d_quote = 0;
}

void	init_job(t_job *job)
{
	job->s_quote = 0;
	job->d_quote = 0;
	job->tem_len = 0;
	job->r_indx = 0;
	job->indx = 0;
	job->in = 0;
	job->out = 1;
	job->rd = 0;
	job->pipe = 0;
}
