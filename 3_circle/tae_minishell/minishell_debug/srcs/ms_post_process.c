/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_post_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:16:54 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 11:18:31 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_post_process_check_single_cmd(t_seq *seq)
{
	if (seq->jobs->size == 1)
	{
		seq->single_cmd_mode = true;
	}
	else
	{
		return ;
	}
}

bool	_post_process_check_path(t_seq *seq)
{
	size_t	idx;
	int		result;
	t_job	*job;

	idx = 0;
	while (idx < seq->jobs->size)
	{
		job = ms_vector_get(seq->jobs, idx);
		if (_check_path_dir(job) == PURE_PATH)
		{
			result = _post_process_join_path(job, seq->path);
			if (result == false)
			{
				return (false);
			}
		}
		++idx;
	}
	return (true);
}

bool	ms_post_process(t_seq *seq)
{
	_post_process_check_single_cmd(seq);
	if (_post_process_check_path(seq) == false)
	{
		return (false);
	}
	else
	{
		return (true);
	}
}
