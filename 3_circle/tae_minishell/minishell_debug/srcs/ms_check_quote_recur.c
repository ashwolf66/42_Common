/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quote_recur.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:11:13 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 11:11:19 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	_check_quote_pair_none(
		t_token *tok, char *prev, int *stat)
{
	if (tok->chunk[0] == '\'' || tok->chunk[0] == '\"')
	{
		*stat = STAT_QUOTE;
		*prev = tok->chunk[0];
	}
	else
	{
		*stat = STAT_UNQUOTE;
	}
}

static bool	_check_quote_pair_quote(
		t_token *tok, char *prev, int *idx, int *stat)
{
	if (*prev == tok->chunk[*idx])
	{
		*stat = STAT_UNQUOTE;
	}
	else
	{
		if (tok->chunk[*idx] == '\0')
		{
			*stat = ERR_PAIR;
			return (false);
		}
	}
	return (true);
}

static bool	_check_quote_pair_unquote(
		t_token *tok, char *prev, int *idx, int *stat)
{
	if (tok->chunk[*idx] == '\'' || tok->chunk[*idx] == '\"')
	{
		*stat = STAT_QUOTE;
		*prev = tok->chunk[*idx];
	}
	else
	{
		if (tok->chunk[*idx] == '\0')
			return (false);
	}
	return (true);
}

static void	ms_check_quote_pair(t_token *tok, char prev, int idx, int *stat)
{
	if (tok->type != FLAG_CMD || tok->chunk == NULL)
	{
		return ;
	}
	else if (*stat == NONE)
	{
		_check_quote_pair_none(tok, &prev, stat);
	}
	else if (*stat == STAT_QUOTE)
	{
		if (_check_quote_pair_quote(tok, &prev, &idx, stat) == false)
			return ;
	}
	else if (*stat == STAT_UNQUOTE)
	{
		if (_check_quote_pair_unquote(tok, &prev, &idx, stat) == false)
			return ;
	}
	ms_check_quote_pair(tok, prev, idx + 1, stat);
}

void	ms_check_quote_recur(t_vector *toks, int idx, int *stat)
{
	t_token	*tok;

	tok = ms_vector_get(toks, idx);
	if (tok->type & FLAG_NEW_LINE)
	{
		return ;
	}
	else
	{
		ms_check_quote_pair(tok, 0, 0, stat);
		if (*stat == ERR_PAIR)
		{
			return ;
		}
		else
		{
			ms_check_quote_recur(toks, idx + 1, stat);
		}
	}
}
