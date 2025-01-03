/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 07:58:11 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 07:58:16 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	one_job(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[])
{
	if (job->rd)
		set_in_out(job->in, job->out);
	ft_builtin(o_job, job, b_info, all_pid);
}
