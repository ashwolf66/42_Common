/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipeline_detect_err.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:15:06 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 11:15:11 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ms_pipeline_detect_err(t_system *system)
{
	if (ms_print_syntax_err(&system->input))
	{
		return (false);
	}
	if (ms_detect_parse_err(system->input.vector) == false)
	{
		system->prompt = "> ";
		system->need_pair = true;
		return (false);
	}
	else
	{
		system->prompt = "minishell> ";
		system->need_pair = false;
		return (true);
	}
}
