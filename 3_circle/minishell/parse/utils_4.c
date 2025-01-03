/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 07:18:57 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:17:07 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	direct_check_utils(t_commend *com)
{
	if (com->cmd[com->indx] == '<' && com->di_space == 0)
		com->l_direct++;
	else if (com->cmd[com->indx] == '>' && com->di_space == 0)
		com->r_direct++;
	else if (com->cmd[com->indx] == '<' && com->di_space != 0)
		com->l_direct = -1;
	else if (com->cmd[com->indx] == '>' && com->di_space != 0)
		com->r_direct = -1;
}

int	fd_start_utils(char **temp, t_job *job, t_info *b_info, int *j)
{
	if (job->job[job->r_indx] && ((job->r_indx > 0
				&& (job->job[job->r_indx - 1][0] == '<'
				|| job->job[job->r_indx - 1][0] == '>'))))
	{
		if (fd_result(job, b_info))
		{
			free_mem(temp);
			temp = NULL;
			return (1);
		}
		job->r_indx++;
		return (2);
	}
	temp[*j] = ft_strdup(job->job[job->r_indx]);
	if (!temp[*j])
	{
		free_mem(temp);
		temp = NULL;
		return (1);
	}
	return (0);
}

int	ms_return_1(char *str, int i)
{
	return ((str[i] < 'A' || str[i] > 'Z')
		&& (str[i] < 'a' || str[i] > 'z') && str[i] != '_');
}

int	ms_return_2(char *str, int i)
{
	return (((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a'
				&& str[i] <= 'z') || str[i] == '_' || (str[i] >= '0'
				&& str[i] <= '9')) && str[i] != '\0');
}

int	ms_utils_1(char *str, t_commend *com, int len, int i)
{
	com->temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!com->temp)
		return (0);
	ms_cpy_temp(com, str, i, len);
	return (1);
}
