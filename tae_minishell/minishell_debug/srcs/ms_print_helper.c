/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:01:14 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 12:37:53 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//print ms_split_cmd, get_chunks result
void	ms_print_vec(t_vector *vector)
{
	size_t	idx;
	void	*ret;

	idx = 0;
	while (idx < vector->size)
	{
		ret = ms_vector_get(vector, idx);
		printf("%zu : [%s]\n", idx, (char *)ret);
		++idx;
	}
}

//print ms_lexer result
void	ms_print_token(t_vector *tokens, size_t dst)
{
	size_t	idx;
	t_token	*token;
	size_t	lim;

	idx = 0;
	if (dst == tokens->size)
		lim = tokens->size;
	else
		lim = dst + 1;
	while (idx < lim)
	{
		token = ms_vector_get(tokens, idx);
		printf("[%zu] ", idx);
		if (token->type == FLAG_NEW_LINE)
			printf("type : [%s] ", "NEW_LINE");
		else if (token->type == FLAG_PIPE)
			printf("type : [%s] ", "PIPE");
		else if (token->type == FLAG_IN_REDIR)
			printf("type : [%s] ", "IN_REDIR");
		else if (token->type == FLAG_HERE_DOC)
			printf("type : [%s] ", "HERE_DOC");
		else if (token->type == FLAG_OUT_REDIR)
			printf("type : [%s] ", "OUT_REDIR");
		else if (token->type == FLAG_OUT_REDIR_APP)
			printf("type : [%s] ", "OUT_REDIR_APPEND");
		else if (token->type == FLAG_CMD)
			printf("type : [%s] ", "CMD");
		else
			printf("type : [%s] ", "NONE");
		printf("chunk : [%s]\n", token->chunk);
		++idx;
	}
}

void	ms_print_dic(t_vector *dic)
{
	t_envp	*envp;
	size_t	idx;

	idx = 0;
	while (idx < dic->size)
	{
		envp = ms_vector_get(dic, idx);
		printf("key : [%s] value : [%s]\n", envp->key, envp->value);
		++idx;
	}
}

void	ms_print_parse_result(t_system *system)
{
	t_seq	seq;
	t_job	*job;
	t_file	*temp;
	char	*arg;
	size_t	idx;
	size_t	i;

	seq = system->seq;
	printf("[SEQ] single_cmd_mode : %d\n\n", seq.single_cmd_mode);
	idx = 0;
	while (idx < seq.jobs->size)
	{
		i = 0;
		job = ms_vector_get(seq.jobs, idx);
		printf("[%zu] [SEQ] job infiles\n", idx);
		while (i < job->infiles->size)
		{
			temp = ms_vector_get(job->infiles, i);
			printf("type : %d, io_target : [%s]\n",
				temp->type, temp->io_target);
			++i;
		}
		i = 0;
		printf("\n");
		printf("[%zu] [SEQ] job outfiles\n", idx);
		while (i < job->outfiles->size)
		{
			temp = ms_vector_get(job->outfiles, i);
			printf("type : %d, io_target : [%s]\n",
				temp->type, temp->io_target);
			++i;
		}
		printf("\n");
		printf("[%zu] [SEQ] cmd : [%s]\n\n", idx, job->cmd);
		i = 0;
		printf("[%zu] [SEQ] arg\n", idx);
		while (i < job->arg->size)
		{
			arg = ms_vector_get(job->arg, i);
			printf("arg : [%s]\n", arg);
			++i;
		}
		printf("\n");
		++idx;
		printf("[SEQ] is_builtin : %d]\n", job->is_builtin);
	}
}
