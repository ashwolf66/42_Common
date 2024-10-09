/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipeline_tokenize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:14:26 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 13:59:33 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

void	ms_pipeline_tokenize(t_system *system)
{
	ms_init_input(&system->input);
	if (system->need_pair == true)
	{
		system->backup = ms_strjoin_s(
				system->backup, ms_readline(system->prompt));
	}
	else
	{
		system->backup = ms_readline(system->prompt);
	}
	add_history(system->backup);
	system->input.line = ms_strdup(system->backup);
	if (ms_strcmp(system->input.line, "exit") == 0)
	{
		ms_exit(g_exit_code, NULL, 1);
	}
	ms_get_chunks(
		system->input.vector, &system->input.line, &system->input.output);
	ms_clean_blank(system->input.vector);
	printf("[AFTER SPLIT COMMAND LINE]\n");
	ms_print_vec(system->input.vector);
	ms_tokenizer(&system->input.info);
	printf("[AFTER TOKENIZE STAGE]\n");
	ms_print_token(system->input.vector, system->input.vector->size);
}
