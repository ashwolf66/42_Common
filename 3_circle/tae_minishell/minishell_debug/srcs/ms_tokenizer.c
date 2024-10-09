/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenzier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:07:52 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/13 09:08:21 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ms_state_none(t_info *info)
{
	info->temp = ms_vector_get(info->chunk, info->idx);
	info->token->type = ms_scan_type(info->temp);
	info->token->chunk = info->temp;
	info->chunk->data[info->idx] = info->token;
	if (info->token->type & FLAG_PIPE)
	{
		info->state = ERR_SYN;
		return (1);
	}
	info->prev_t = info->token->type;
	info->state = STAT_ORD;
	++info->idx;
	return (0);
}

static int	ms_state_ord(t_info *info)
{	
	info->temp = ms_vector_get(info->chunk, info->idx);
	info->token->type = ms_scan_type(info->temp);
	info->token->chunk = info->temp;
	info->chunk->data[info->idx] = info->token;
	ms_check_syntax(&info->state, info->prev_t, info->token->type);
	if (info->state == ERR_SYN)
		return (1);
	info->prev_t = info->token->type;
	if (info->token->type & MASK_OPERATOR)
		info->state = STAT_OPR;
	++info->idx;
	return (0);
}

static int	ms_state_opr(t_info *info)
{
	info->temp = ms_vector_get(info->chunk, info->idx);
	info->token->type = ms_scan_type(info->temp);
	info->token->chunk = info->temp;
	info->chunk->data[info->idx] = info->token;
	ms_check_syntax(&info->state, info->prev_t, info->token->type);
	if (info->state == ERR_SYN)
		return (1);
	info->prev_t = info->token->type;
	info->state = STAT_OPR;
	++info->idx;
	return (0);
}

void	ms_tokenizer(t_info *info)
{
	info->token = ms_init_token(ms_malloc(sizeof(t_token) * 1));
	if (info->idx == info->chunk->size)
		return ;
	else if (info->state == NONE)
	{
		if (ms_state_none(info))
			return ;
	}
	else if (info->state == STAT_ORD)
	{
		if (ms_state_ord(info))
			return ;
	}
	else if (info->state == STAT_OPR)
	{
		if (ms_state_opr(info))
			return ;
	}
	ms_tokenizer(info);
}
