/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipeline_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:16:18 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 11:16:28 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ms_pipeline_parse(t_system *system)
{
	t_job	*job;
	t_token	*token;
	int		idx;

	job = NULL;
	idx = 0;
	token = ms_vector_get(system->input.vector, idx);
	while (!(token->type & FLAG_NEW_LINE))
	{
		job = ms_make_job(system->input.vector, &idx);
		ms_vector_add(system->seq.jobs, job);
		token = ms_vector_get(system->input.vector, idx);
	}
	if (ms_post_process(&system->seq) == false)
	{
		return (false);
	}
	else
	{
		return (true);
	}
}
