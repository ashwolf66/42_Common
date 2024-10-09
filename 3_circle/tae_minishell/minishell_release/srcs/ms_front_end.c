/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_front_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 10:45:59 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 10:15:27 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

bool	ms_front_end(t_system *system)
{
	ms_pipeline_tokenize(system);
	if (ms_pipeline_detect_err(system) == false)
	{
		return (false);
	}
	ms_pipeline_expansion(system);
	if (ms_pipeline_parse(system) == false)
	{
		return (ERR_FRONT_END);
	}
	return (true);
}
