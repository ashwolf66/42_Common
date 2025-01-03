/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 07:19:12 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 07:19:47 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	is_whitespace(char chr)
{
	if (chr == ' ' || (chr >= 9 && chr <= 13))
		return (1);
	return (0);
}

int	is_quote(char chr)
{
	if (chr == '\'' || chr == '"')
		return (1);
	return (0);
}

void	c_quote_check(t_commend *com)
{
	if (com->cmd[com->indx] == '\'' && com->d_quote == 0)
		com->s_quote = !com->s_quote;
	else if (com->cmd[com->indx] == '"' && com->s_quote == 0)
		com->d_quote = !com->d_quote;
}

void	p_quote_check(t_pool *pool)
{
	if (pool->cmd_pool[pool->r_indx][pool->indx] == '\'' && pool->d_quote == 0)
		pool->s_quote = !pool->s_quote;
	else if (pool->cmd_pool[pool->r_indx][pool->indx] == '"'
		&& pool->s_quote == 0)
		pool->d_quote = !pool->d_quote;
}

void	add_c_quote_check(t_commend *com, t_pool *pool, t_info *b_info)
{
	if (!com->cmd[com->indx])
		cmd_pipe_mal(com, pool, b_info);
	if (com->cmd[com->indx] == '\'' && com->d_quote == 0)
		com->s_quote = !com->s_quote;
	else if (com->cmd[com->indx] == '"' && com->s_quote == 0)
		com->d_quote = !com->d_quote;
	if (com->cmd[com->indx] != '$')
	{
		com->count++;
		com->indx++;
	}
}
