/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 07:07:43 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 07:07:58 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	syn_c_quote_check(t_commend *com)
{
	if (com->cmd[com->indx] == '\'' && com->d_quote == 0)
		com->s_quote = !com->s_quote;
	else if (com->cmd[com->indx] == '"' && com->s_quote == 0)
		com->d_quote = !com->d_quote;
}
