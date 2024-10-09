/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:57:34 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/16 10:49:41 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_is_redir(char *output)
{
	if (ms_strcmp(output, "<") == 0
		|| ms_strcmp(output, ">") == 0
		|| ms_strcmp(output, "<<") == 0
		|| ms_strcmp(output, ">>") == 0)
		return (1);
	return (0);
}

void	ms_split_cmd(char **input, char **output, char pair, int state)
{
	if (state == NONE)
		ms_handle_none(input, output, &pair, &state);
	else if (state == UNQUOTED)
		ms_handle_unquoted(input, output, &pair, &state);
	else if (state == QUOTED)
		ms_handle_quoted(input, output, pair, &state);
}

void	ms_handle_none(char **input, char **output, char *pair, int *state)
{
	if ((*input)[0] == '\'' || (*input)[0] == '\"')
	{
		*state = QUOTED;
		*pair = **input;
	}
	else
		*state = UNQUOTED;
	*output = ms_strjoin_s(*output, ms_strndup((*input)++, 1));
	ms_split_cmd(input, output, *pair, *state);
}

void	ms_handle_unquoted(char **input, char **output, char *pair, int *state)
{
	if (ms_strcmp(*output, "|") == 0 || ms_is_redir(*output) || **input == '\0'
		|| ms_is_set(**input, " \t<>|"))
	{
		if (ms_is_redir(*output) && ms_is_set(**input, "<>"))
		{
			if (**output == **input)
				*output = ms_strjoin_s(*output, ms_strndup((*input)++, 1));
		}
		else if (ms_strcmp(*output, "|") == 0)
			return ;
		return ;
	}
	else if (ms_is_set(**input, "\'\""))
	{
		*state = QUOTED;
		*pair = **input;
		*output = ms_strjoin_s(*output, ms_strndup((*input)++, 1));
		ms_split_cmd(input, output, *pair, *state);
	}
	else
	{
		*output = ms_strjoin_s(*output, ms_strndup((*input)++, 1));
		ms_split_cmd(input, output, *pair, *state);
	}
}

void	ms_handle_quoted(char **input, char **output, char pair, int *state)
{
	if (**input == pair)
	{
		*state = UNQUOTED;
		*output = ms_strjoin_s(*output, ms_strndup((*input)++, 1));
		ms_split_cmd(input, output, pair, *state);
	}
	else if (**input == '\0')
		return ;
	else
	{
		*output = ms_strjoin_s(*output, ms_strndup((*input)++, 1));
		ms_split_cmd(input, output, pair, *state);
	}
}
