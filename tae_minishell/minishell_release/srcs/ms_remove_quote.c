/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:07:18 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/16 10:55:35 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_rq
{
	int		idx;
	int		state;
	char	prev;
	char	*input;
	char	*output;
}	t_rq;

static bool	_remove_quote_none(t_rq *param)
{
	if (param->input[param->idx] == '\0')
		return (false);
	if (param->input[param->idx] == '\'' || param->input[param->idx] == '\"')
	{
		param->prev = param->input[param->idx];
		param->state = STAT_QUOTE;
	}
	else if (param->input[param->idx] == '$'
		&& param->input[param->idx + 1] == '\0')
	{
		param->output = ms_strjoin_s(
				param->output, ms_strndup(&param->input[param->idx], 1));
		return (false);
	}
	else if (param->input[param->idx] == '$')
	{
		param->state = STAT_UNQUOTE;
	}
	else
	{
		param->state = STAT_UNQUOTE;
		param->output = ms_strjoin_s(
				param->output, ms_strndup(&param->input[param->idx], 1));
	}
	return (true);
}

static void	_remove_quote_quote(t_rq *param)
{
	if (param->prev == param->input[param->idx])
	{
		param->state = NONE;
		param->prev = 0;
	}
	else
	{
		param->output = ms_strjoin_s(
				param->output, ms_strndup(&param->input[param->idx], 1));
	}
}

static bool	_remove_quote_unquote(t_rq *param)
{
	if (param->input[param->idx] == '\0')
		return (false);
	if (param->input[param->idx] == '\'' || param->input[param->idx] == '\"')
	{
		param->prev = param->input[param->idx];
		param->state = STAT_QUOTE;
	}
	else
	{
		param->output = ms_strjoin_s(
				param->output, ms_strndup(&param->input[param->idx], 1));
	}
	return (true);
}

static void	_remove_quote(t_rq *param)
{
	if (param->input == NULL)
		return ;
	if (param->state == NONE)
	{
		if (_remove_quote_none(param) == false)
			return ;
		param->idx += 1;
		_remove_quote(param);
	}
	else if (param->state == STAT_QUOTE)
	{	
		_remove_quote_quote(param);
		param->idx += 1;
		_remove_quote(param);
	}
	else if (param->state == STAT_UNQUOTE)
	{
		if (_remove_quote_unquote(param) == false)
			return ;
		param->idx += 1;
		_remove_quote(param);
	}
}

void	ms_remove_quote(t_vector *toks)
{
	t_token	*tok;
	size_t	idx;
	t_rq	rq;

	idx = 0;
	while (idx < toks->size - 1)
	{
		tok = ms_vector_get(toks, idx);
		if (tok->type == FLAG_CMD)
		{
			rq.idx = 0;
			rq.state = NONE;
			rq.prev = 0;
			rq.input = tok->chunk;
			rq.output = NULL;
			_remove_quote(&rq);
			tok->chunk = rq.output;
		}
		++idx;
	}
}
