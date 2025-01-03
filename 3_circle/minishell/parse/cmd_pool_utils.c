/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pool_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:41:40 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:43:49 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	direct_case(t_commend *com)
{
	return (com->indx > 0 && (com->cmd[com->indx] == '<'
			|| com->cmd[com->indx] == '>')
		&& com->cmd[com->indx] != com->cmd[com->indx - 1]
		&& !is_whitespace(com->cmd[com->indx - 1]));
}

int	un_direct_case(t_commend *com)
{
	return (com->indx > 0 && com->cmd[com->indx] != '<'
		&& com->cmd[com->indx] != '>' && !is_whitespace(com->cmd[com->indx])
		&& (com->cmd[com->indx - 1] == '<'
			|| com->cmd[com->indx - 1] == '>'));
}

void	env_check(t_commend *com, t_info *b_info)
{
	com->temp = NULL;
	com->len = get_env_len(com);
	if (com->s_quote == 1 || com->len == 0 || com->temp == NULL)
	{
		com->count++;
		com->indx++;
		return ;
	}
	if (!ps_find_list_key(b_info->exp_list, com))
	{
		com->temp[0] = '\0';
		com->temp_len += com->len;
	}
	com->indx += com->len + 1;
	if (com->cmd[com->indx] == '\0')
		com->indx--;
	free(com->temp);
}

int	get_env_len(t_commend *com)
{
	int	i;
	int	len;

	len = 0;
	i = com->indx + 1;
	if ((com->cmd[i] < 'A' || com->cmd[i] > 'Z') && (com->cmd[i] < 'a'
			|| com->cmd[i] > 'z') && com->cmd[i] != '_')
		return (0);
	while (((com->cmd[i] >= 'A' && com->cmd[i] <= 'Z')
			|| (com->cmd[i] >= 'a' && com->cmd[i] <= 'z')
			|| com->cmd[i] == '_' || (com->cmd[i] >= '0'
				&& com->cmd[i] <= '9')) && com->cmd[i] != '\0')
	{
		len++;
		i++;
	}
	i = com->indx + 1;
	com->temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!com->temp)
		return (0);
	cpy_temp(com, i, len);
	return (len);
}
