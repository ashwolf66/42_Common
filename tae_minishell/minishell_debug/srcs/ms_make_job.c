/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_make_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:15:49 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 13:59:24 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_pipeline_expansion(t_system *system)
{
	ms_sh_param_expan(system->input.vector, system->seq.dic);
	printf("[AFTER SHELL PARAMETER EXPANSION handling \'$\']\n");
	ms_print_token(system->input.vector, system->input.vector->size);
	ms_remove_quote(system->input.vector);
	printf("[AFTER QUOTE REMOVE EXPANSION]\n");
	ms_print_token(system->input.vector, system->input.vector->size);
}

void	ms_init_job(t_job *job)
{
	job->infiles = ms_vector_create();
	job->outfiles = ms_vector_create();
	job->arg = ms_vector_create();
	job->cmd = NULL;
	job->is_builtin = false;
}

static void	_make_job_handle_infile(t_mj *mj, t_vector *toks, int *idx)
{
	t_file	*file;
	t_token	*tok;

	file = ms_malloc(sizeof(t_file));
	file->type = mj->tok->type;
	++(*idx);
	tok = ms_vector_get(toks, *idx);
	file->io_target = tok->chunk;
	ms_vector_add(mj->job->infiles, file);
}

static void	_make_job_handle_outfile(t_mj *mj, t_vector *toks, int *idx)
{
	t_file	*file;
	t_token	*tok;

	file = ms_malloc(sizeof(t_file));
	file->type = mj->tok->type;
	++(*idx);
	tok = ms_vector_get(toks, *idx);
	file->io_target = tok->chunk;
	ms_vector_add(mj->job->outfiles, file);
}

t_job	*ms_make_job(t_vector *toks, int *idx)
{
	t_mj	mj;

	mj.job = ms_malloc(sizeof(t_job));
	ms_init_job(mj.job);
	mj.tok = ms_vector_get(toks, *idx);
	while ((mj.tok->type != FLAG_NEW_LINE) && (mj.tok->type != FLAG_PIPE))
	{
		if (mj.tok->type & (FLAG_IN_REDIR | FLAG_HERE_DOC))
			_make_job_handle_infile(&mj, toks, idx);
		else if (mj.tok->type & (FLAG_OUT_REDIR | FLAG_OUT_REDIR_APP))
			_make_job_handle_outfile(&mj, toks, idx);
		else if (mj.tok->type & FLAG_CMD)
			ms_vector_add(mj.job->arg, mj.tok->chunk);
		++(*idx);
		mj.tok = ms_vector_get(toks, *idx);
	}
	mj.job->cmd = ms_vector_get(mj.job->arg, 0);
	if (mj.tok->type & FLAG_PIPE)
		++(*idx);
	return (mj.job);
}
