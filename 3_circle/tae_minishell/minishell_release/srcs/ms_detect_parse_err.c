/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_detect_parse_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:49:58 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/16 11:17:26 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_detect_parse_err(t_vector *toks)
{
	int	pip_stat;
	int	quote_stat;

	pip_stat = NONE;
	quote_stat = NONE;
	ms_check_pipe_pair_recur(toks, 0, &pip_stat, 0);
	ms_check_quote_recur(toks, 0, &quote_stat);
	if (pip_stat == ERR_PAIR || quote_stat == ERR_PAIR)
	{
		return (false);
	}
	else
	{
		return (true);
	}
}
