/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:23:54 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:24:08 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	parent_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signal_handle(int signal)
{
	write(2, "\n", 1);
	g_status = 130;
	exit(g_status);
	(void)signal;
}

void	heredoc_signal(void)
{
	signal(SIGINT, heredoc_signal_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handle(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = (signal + 128) << 8;
	(void)signal;
}

void	set_signal(void)
{
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, SIG_IGN);
}
