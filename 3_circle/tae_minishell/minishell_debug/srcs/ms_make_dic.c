/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_make_dic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:46:17 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/14 09:47:35 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_make_dic(char **envp, t_vector *dic, int idx)
{
	t_envp	*elem;
	char	**temp;

	elem = ms_malloc(sizeof(t_envp));
	if (envp[idx] == NULL)
	{
		elem->key = NULL;
		elem->value = NULL;
		ms_vector_add(dic, elem);
		return ;
	}
	else
	{
		temp = ms_split(envp[idx], '=');
		elem->key = temp[0];
		elem->value = temp[1];
		ms_vector_add(dic, elem);
		ms_make_dic(envp, dic, idx + 1);
	}
}
