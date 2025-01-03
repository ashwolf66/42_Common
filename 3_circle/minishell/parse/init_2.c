/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 09:03:12 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 09:03:13 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	exe_init_job(t_job *job)
{
	job->s_quote = 0;
	job->d_quote = 0;
	job->tem_len = 0;
	job->r_indx = 0;
	job->indx = 0;
	job->pipe = 0;
}
