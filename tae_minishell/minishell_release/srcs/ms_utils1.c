/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_globals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:06:33 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 11:08:25 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_init_input(t_input *input)
{
	input->line = NULL;
	input->output = NULL;
	input->state = NONE;
	input->vector = ms_vector_create();
	ms_init_info(&input->info, input->vector);
}

void	ms_init_seq(t_seq *seq, char **envp)
{
	char	**path;
	size_t	idx;

	idx = 0;
	seq->dic = ms_vector_create();
	ms_make_dic(envp, seq->dic, 0);
	seq->path = ms_vector_create();
	path = ms_split(ms_search_value(seq->dic, "PATH"), ':');
	while (path[idx])
	{
		ms_vector_add(seq->path, path[idx]);
		++idx;
	}
	seq->jobs = ms_vector_create();
	seq->single_cmd_mode = false;
}

int	ms_print_syntax_err(t_input *input)
{
	int	res;

	if (input->info.state == ERR_SYN)
	{
		res = ms_strcmp(
				((t_token *)(input->vector->data[input->info.idx]))->chunk,
				"\n");
		if (res == 0)
		{
			printf("minishell: syntax error near unexpected token \'%s\'\n",
				"newline");
			return (1);
		}
		else
		{
			printf("minishell: syntax error near unexpected token \'%s\'\n",
				((t_token *)(input->vector->data[input->info.idx]))->chunk);
			return (1);
		}
	}
	return (0);
}
