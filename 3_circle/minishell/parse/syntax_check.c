/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:22:30 by jacha             #+#    #+#             */
/*   Updated: 2025/01/01 19:00:18 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	syntax_check(t_commend *com)
{
	if (!(com->cmd[com->indx]) && (((com->s_quote == 1 || com->d_quote == 1))
			|| (com->l_count != 0 || com->r_count != 0)))
		return (1);
	else if (!(com->cmd[com->indx]))
		return (0);
	if (com->l_direct == -1 || com->r_direct == -1)
		return (1);
	if (com->cmd[com->indx] == '|' && (com->pipe == 1
			|| com->cmd[com->indx + 1] == '\0'))
		return (1);
	if (com->cmd[com->indx] == '|' && com->pipe == 0)
		com->pipe = 1;
	else if (!is_whitespace(com->cmd[com->indx]))
		com->pipe = 0;
	if (com->cmd[com->indx] == '<' || com->cmd[com->indx] == '>')
		direct_check(com);
	else if (com->cmd[com->indx] != '<' || com->cmd[com->indx] != '>')
		direct_check(com);
	if (direct_count(com))
		return (1);
	syn_c_quote_check(com);
	com->indx++;
	return (syntax_check(com));
}

int	direct_count(t_commend *com)
{
	if (com->cmd[com->indx] == '<')
		com->l_count++;
	else if (com->cmd[com->indx] == '>')
		com->r_count++;
	if (com->l_count > 2 || com->r_count > 2)
		return (1);
	if (com->cmd[com->indx] != '<' && (com->cmd[com->indx] != '|'
			|| com->cmd[com->indx] != '\0'))
		com->l_count = 0;
	if (com->cmd[com->indx] != '>' && (com->cmd[com->indx] != '|'
			|| com->cmd[com->indx] != '\0'))
		com->r_count = 0;
	return (0);
}

void	syntax_error(t_commend *com, t_pool *pool)
{
	printf("syntax error\n");
	free(com->cmd);
	free(com);
	free(pool);
}
