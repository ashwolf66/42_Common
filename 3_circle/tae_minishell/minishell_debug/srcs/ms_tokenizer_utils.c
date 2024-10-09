/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:06:18 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/13 09:13:50 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_clean_blank(t_vector *vector)
{
	size_t	idx;
	char	*chunk;

	idx = 0;
	while (idx < vector->size)
	{
		chunk = ms_vector_get(vector, idx);
		if (ms_strcmp(chunk, " ") == 0)
			ms_vector_remove(vector, idx);
		else
		{
			vector->data[idx] = ms_strtrim(vector->data[idx], " \t");
			++idx;
		}
	}
}

t_token	*ms_init_token(t_token *token)
{
	token->type = NONE;
	token->chunk = NULL;
	return (token);
}

int	ms_scan_type(char *chunk)
{
	if (ms_strcmp(chunk, "<") == 0)
		return (FLAG_IN_REDIR);
	else if (ms_strcmp(chunk, "<<") == 0)
		return (FLAG_HERE_DOC);
	else if (ms_strcmp(chunk, ">") == 0)
		return (FLAG_OUT_REDIR);
	else if (ms_strcmp(chunk, ">>") == 0)
		return (FLAG_OUT_REDIR_APP);
	else if (ms_strcmp(chunk, "|") == 0)
		return (FLAG_PIPE);
	else if (ms_strcmp(chunk, "\n") == 0)
		return (FLAG_NEW_LINE);
	else
		return (FLAG_CMD);
}

void	ms_check_syntax(int *state, int prev_t, int current_t)
{
	if ((prev_t & (FLAG_IN_REDIR | FLAG_OUT_REDIR))
		&& (current_t & (FLAG_IN_REDIR | FLAG_OUT_REDIR))
		&& (prev_t ^ current_t))
	{
		*state = ERR_SYN;
	}
	else if ((prev_t & FLAG_PIPE)
		&& (current_t & (MASK_OPERATOR ^ (MASK_REDIR | FLAG_NEW_LINE))))
	{
		*state = ERR_SYN;
	}
	else if ((prev_t & MASK_REDIR) && (current_t & MASK_OPERATOR))
	{
		*state = ERR_SYN;
	}
}

void	ms_init_info(t_info *info, t_vector *chunk)
{
	info->token = NULL;
	info->temp = NULL;
	info->chunk = chunk;
	info->idx = 0;
	info->state = NONE;
	info->prev_t = NONE;
}
