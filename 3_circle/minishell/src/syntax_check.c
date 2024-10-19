/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:12:49 by jacha             #+#    #+#             */
/*   Updated: 2024/10/19 12:51:26 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check(t_commend com)
{
	while (*cmd)
	{
		if (*cmd == '|' && com->pipe == 0)
			break ;
		else if (*cmd == '|' && com->pipe == 1)
			com->pipe = 0;
		if (*cmd == '\'')
			qoute_check(&(com->s_qoute));
		else if (*cmd == '\"')
			qoute_check(&(com->d_qoute));
		cmd++;
	}
	return (0);
}

void	qoute_check(int *qoute)
{
		if (*qoute == 0)
			*qoute = 1;
		else if (*qoute == 1)
			*qoute = 0;
}
