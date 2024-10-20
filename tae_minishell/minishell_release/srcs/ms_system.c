/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:40:30 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/16 10:49:10 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_reset_system(t_seq *seq)
{
	seq->jobs = ms_vector_create();
	seq->single_cmd_mode = false;
}

void	ms_init_system(t_system *system, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	system->need_pair = false;
	system->backup = NULL;
	system->prompt = "minishell> ";
	ms_init_seq(&system->seq, envp);
}
