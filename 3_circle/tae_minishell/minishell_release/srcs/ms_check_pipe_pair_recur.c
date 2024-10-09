/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_pipe_pair_recur.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:11:39 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 11:11:48 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_check_pipe_pair_recur(
		t_vector *toks, int idx, int *stat, int prev)
{
	t_token	*tok;

	tok = ms_vector_get(toks, idx);
	if (tok->type & FLAG_NEW_LINE)
	{
		if (prev & FLAG_PIPE)
			*stat = ERR_PAIR;
		return ;
	}
	else
	{
		if (prev & FLAG_PIPE)
			prev = NONE;
		if (tok->type & FLAG_PIPE)
			prev = FLAG_PIPE;
		ms_check_pipe_pair_recur(toks, idx + 1, stat, prev);
	}
}
