/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:33:03 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:33:13 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

t_job	*ms_lstnew(char **job, int num)
{
	t_job	*n_node;
	char	**temp;

	n_node = malloc(sizeof(t_job));
	if (!n_node)
		return (0);
	temp = ms_strdup(job);
	n_node->job = temp;
	n_node->num = num;
	n_node->next = NULL;
	free_mem(job);
	job = NULL;
	return (n_node);
}
