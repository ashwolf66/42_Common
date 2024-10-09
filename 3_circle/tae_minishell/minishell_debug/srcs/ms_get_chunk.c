/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:09:56 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 11:10:07 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_get_chunks(t_vector *chunks, char **input, char **output)
{
	char	*nl;

	if (**input == '\0')
	{
		nl = ms_malloc(sizeof(char) * 2);
		nl[0] = '\n';
		nl[1] = '\0';
		ms_vector_add(chunks, (void *)nl);
		return ;
	}
	else
	{
		ms_split_cmd(input, output, 0, 0);
		ms_vector_add(chunks, (void *)*output);
		*output = NULL;
		ms_get_chunks(chunks, input, output);
	}
}
