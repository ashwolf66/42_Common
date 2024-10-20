/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _sh_param_expan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:12:58 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 12:22:56 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static char	*_env_expansion(char *key, t_vector *dic)
{
	char	*value;

	value = ms_search_value(dic, key);
	return (value);
}

static char	*_param_expansion(char *input, size_t *idx, t_vector *dic)
{
	char	*output;

	output = NULL;
	if (input[1] == '?')
	{
		++(*idx);
		output = ms_itoa(g_exit_code);
		++(*idx);
	}
	else if (ms_isalnum_und(input[1]) == true)
	{
		++(*idx);
		output = _env_expansion(ms_strdup_to_key(&input[1], idx), dic);
	}
	else
	{
		++(*idx);
	}
	return (output);
}

static char	*_handle_dollar(char *input, size_t *idx, t_vector *dic)
{
	char	*output;

	output = NULL;
	if (ms_is_set(input[1], " \t") || input[1] == '\0')
	{
		output = ms_strjoin_s(output, ms_strndup(input, 1));
		++(*idx);
	}
	else
	{
		output = ms_strjoin_s(output, _param_expansion(input, idx, dic));
	}
	return (output);
}

char	*_sh_param_expan(char *chunk, t_vector *dic)
{
	char	*output;
	size_t	idx;

	output = NULL;
	idx = 0;
	while (chunk[idx])
	{
		if (ms_cal_quote_stat(chunk[idx]) == false && chunk[idx] == '$')
		{
			output = ms_strjoin_s(
					output, _handle_dollar(&chunk[idx], &idx, dic));
		}
		else
		{
			output = ms_strjoin_s(
					output, ms_strndup(&chunk[idx], 1));
			++idx;
		}
	}
	return (output);
}
