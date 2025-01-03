/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pool_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 07:59:11 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 07:59:39 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	cpy_temp(t_commend *com, int i, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		com->temp[j] = com->cmd[i];
		i++;
		j++;
	}
	com->temp[j] = '\0';
}

int	ps_find_list_key(t_list *head, t_commend *cmd)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(cmd->temp, current->key) == 0)
		{
			free(cmd->temp);
			cmd->temp = ft_strdup(current->val);
			cmd->temp_len += ft_strlen(cmd->temp);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
