/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 07:20:00 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 07:52:57 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	update_fd(t_job **job, t_info *b_info)
{
	t_job	*temp;

	temp = *job;
	while (temp != NULL)
	{
		init_job(temp);
		if (fd_seting(temp, b_info))
		{
			free_parse(job, &b_info);
			return (1);
		}
		if ((*job)->job[0] == NULL)
			(*job)->job[0] = ft_strdup("EMPTY");
		temp = temp->next;
	}
	return (0);
}

int	fd_seting(t_job *job, t_info *b_info)
{
	int		i;
	int		count;
	char	**temp;

	i = 0;
	count = 0;
	while (job->job[i])
	{
		if (fd_seting_utils(job, &i))
			continue ;
		count++;
		i++;
	}
	temp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!temp)
		return (1);
	temp = fd_start(temp, job, b_info);
	if (!temp)
		return (1);
	free_mem(job->job);
	job->job = NULL;
	job->job = temp;
	return (0);
}

char	**fd_start(char **temp, t_job *job, t_info *b_info)
{
	int	j;
	int	sin;

	j = 0;
	while (job->job[job->r_indx])
	{
		if (job->job[job->r_indx][0] == '<' || job->job[job->r_indx][0] == '>')
		{
			job->r_indx++;
			continue ;
		}
		sin = fd_start_utils(temp, job, b_info, &j);
		if (sin == 1)
			return (NULL);
		else if (sin == 2)
			continue ;
		else
		{
			j++;
			job->r_indx++;
		}
	}
	temp[j] = NULL;
	return (temp);
}

int	fd_result(t_job *job, t_info *b_info)
{
	int	r_d;
	int	l_d;
	int	col;

	if (job->r_indx == 0 || !job->job[job->r_indx - 1])
		return (1);
	r_d = 0;
	l_d = 0;
	col = 0;
	while (job->job[job->r_indx - 1][col])
	{
		if (job->job[job->r_indx - 1][col] == '<')
			l_d++;
		else if (job->job[job->r_indx - 1][col] == '>')
			r_d++;
		col++;
	}
	if (l_d != 0)
		l_dr_case(l_d, job, b_info);
	else if (r_d != 0)
		r_dr_case(r_d, job);
	if (job->in == -1 || job->out == -1)
		return (1);
	job->rd = 1;
	return (0);
}

int	fd_seting_utils(t_job *job, int *i)
{
	if (job->job[*i][0] == '<' || job->job[*i][0] == '>')
	{
		(*i)++;
		return (1);
	}
	if (job->job[job->r_indx] && ((job->r_indx > 0
				&& (job->job[job->r_indx - 1][0] == '<'
				|| job->job[job->r_indx - 1][0] == '>'))))
	{
		(*i)++;
		return (1);
	}
	return (0);
}
