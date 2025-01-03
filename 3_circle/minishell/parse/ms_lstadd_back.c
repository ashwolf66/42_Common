/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:33:26 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:34:09 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	ms_lstadd_back(t_job **lst, t_job *new)
{
	t_job	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while ((*lst)->next != NULL)
		{
			*lst = (*lst)->next;
		}
		(*lst)->next = new;
		*lst = temp;
	}
}
