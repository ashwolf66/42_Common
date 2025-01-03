/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:24:23 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:25:09 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	remove_quote(t_job **job)
{
	t_job	*temp;

	init_job(*job);
	temp = *job;
	while (temp != NULL)
	{
		init_job(temp);
		if (push_rm_quote(temp))
		{
			free_job(job);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	push_rm_quote(t_job *temp)
{
	char	**rm;

	rm = ms_rm_strdup(temp);
	if (rm == NULL)
		return (1);
	free_mem(temp->job);
	temp->job = NULL;
	temp->job = rm;
	return (0);
}

char	**ms_rm_strdup(t_job *job)
{
	size_t	row;
	size_t	col_len;
	char	**temp;

	row = dup_row_len(job->job);
	temp = (char **)malloc(sizeof(char *) * (row + 1));
	if (temp == NULL)
		return (NULL);
	while (job->r_indx < row)
	{
		col_len = dup_colum_len(job->job[job->r_indx]);
		temp[job->r_indx] = (char *)malloc(sizeof(char) * (col_len + 1));
		if (temp == NULL)
			return (NULL);
		rm_dup_cpy(temp[job->r_indx], job, col_len);
		job->indx = 0;
		job->tem_len = 0;
		job->r_indx++;
	}
	temp[job->r_indx] = '\0';
	return (temp);
}

void	rm_dup_cpy(char *temp, t_job *s, size_t col_len)
{
	size_t	i;

	i = 0;
	while (s->job[s->r_indx][s->indx] != '\0' && i <= col_len)
	{
		if (j_quote_check(s))
			break ;
		temp[i] = s->job[s->r_indx][s->indx + s->tem_len];
		s->indx++;
		i++;
	}
	temp[i] = '\0';
}
