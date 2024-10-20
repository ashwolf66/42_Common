/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:03:54 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 11:06:03 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ms_is_set(char chr, char *set)
{
	while (*set)
	{
		if (*set == chr)
		{
			return (true);
		}
		++set;
	}
	return (false);
}

void	ms_exit(int status, char *msg, int out_chan)
{
	t_list	**gc;

	gc = ms_glob();
	ms_lstclear(gc, free);
	if (msg != NULL)
	{
		write(out_chan, msg, ms_strlen(msg));
	}
	exit(status);
}

void	ms_detect_exit(const char *input)
{
	if (ms_strcmp(input, "exit") == 0)
	{
		ms_exit(0, NULL, 1);
	}
}

void	ms_collec_mem(void *mem)
{
	t_list	**gc;

	gc = ms_glob();
	ms_lstadd_back(gc, ms_lstnew(mem));
}

void	ms_clear_mem(void)
{
	t_list	**gc;

	gc = ms_glob();
	ms_lstclear(gc, free);
}
