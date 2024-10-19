/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:12:49 by jacha             #+#    #+#             */
/*   Updated: 2024/10/19 15:53:26 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check(t_commend *com)
{
	if (!(*com->cmd))
		return (com->s_qoute == 1 || com->d_qoute == 1);
	if (*com->cmd == '|' && com->pipe == 1)
		return (1) ;
	if (*com->cmd == '|' && com->pipe == 0)
		com->pipe = 1;
	else if (!is_whitespace(*com->cmd))
		com->pipe = 0;
	if (*com->cmd == '\'')
		qoute_check(&(com->s_qoute));
	else if (*com->cmd == '\"')
		qoute_check(&(com->d_qoute));
	com->cmd++;
	return (syntax_check(com));
}

void	qoute_check(int *qoute)
{
	if (*qoute == 0)
		*qoute = 1;
	else if (*qoute == 1)
		*qoute = 0;
}
