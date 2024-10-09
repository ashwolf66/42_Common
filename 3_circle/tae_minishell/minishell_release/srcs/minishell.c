/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:25:20 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/16 10:47:10 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_system	system;

	ms_init_system(&system, argc, argv, envp);
	while (true)
	{
		if (ms_front_end(&system) == ERR_FRONT_END)
		{
			ms_reset_system(&system.seq);
			continue ;
		}
		else
		{
			ms_reset_system(&system.seq);
		}
	}
	ms_exit(g_exit_code, NULL, 1);
}
