/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:23:27 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:23:44 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	sigint_handle(int signal)
{
	printf("\n");
	(void)signal;
}

void	sigquit_handle(int signal)
{
	(void)signal;
}

void	set_in_out(int in, int out)
{
	if (in != 0)
		dup2(in, STDIN_FILENO);
	if (out != 1)
		dup2(out, 1);
}
