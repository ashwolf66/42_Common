/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sh_param_expan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:34:51 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 10:59:33 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

bool	ms_isalnum_und(char chr)
{
	if (ms_isalnum(chr) || chr == '_')
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

char	*ms_strdup_to_key(char *input, size_t *real_idx)
{
	int		len;
	int		idx;
	char	*new;

	len = 0;
	idx = 0;
	while (ms_isalnum_und(input[len]))
	{
		++len;
	}
	new = ms_malloc(sizeof(len) + 1);
	while (idx < len)
	{
		new[idx] = input[idx];
		++idx;
	}
	new[idx] = '\0';
	*real_idx += ms_strlen_s(new);
	return (new);
}

char	*ms_search_value(t_vector *dic, char *key)
{
	t_envp	*elem;
	size_t	idx;

	idx = 0;
	while (idx < dic->size - 1)
	{
		elem = ms_vector_get(dic, idx);
		if (ms_strcmp(elem->key, key) == 0)
		{
			return (ms_strdup(elem->value));
		}
		++idx;
	}
	return (NULL);
}

bool	ms_cal_quote_stat(char chr)
{
	static char	prev = 0;

	if (prev == 0 && (chr == '\'' || chr == '\"'))
	{
		prev = chr;
	}
	else if (prev == chr)
	{
		prev = 0;
	}
	if (prev == '\'')
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void	ms_sh_param_expan(t_vector *toks, t_vector *dic)
{
	size_t	idx;
	t_token	*tok;

	idx = 0;
	while (idx < toks->size)
	{
		tok = ms_vector_get(toks, idx);
		if (tok->type == FLAG_CMD)
		{
			tok->chunk = _sh_param_expan(tok->chunk, dic);
		}
		++idx;
	}
}
