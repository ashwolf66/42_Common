/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 07:08:14 by jacha             #+#    #+#             */
/*   Updated: 2025/01/01 18:59:48 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	direct_check(t_commend *com)
{
	direct_check_utils(com);
	if (com->cmd[com->indx] != '<' && com->cmd[com->indx] != '>'
		&& com->cmd[com->indx] != '|'
		&& !is_whitespace(com->cmd[com->indx]))
	{
		com->di_space = 0;
		com->l_direct = 0;
		com->r_direct = 0;
	}
	else if ((com->l_direct != 0
			|| com->r_direct != 0)
		&& is_whitespace(com->cmd[com->indx]))
		com->di_space++;
	else if (com->l_direct > 0 && (com->cmd[com->indx] == '|'
			|| com->cmd[com->indx] == '\0'))
		com->l_direct = -1;
	else if (com->r_direct > 0 && (com->cmd[com->indx] == '|'
			|| com->cmd[com->indx] == '\0'))
		com->r_direct = -1;
}

size_t	ms_to_strlcpy(char *dest, t_pool *s, size_t size)
{
	size_t	src_len;
	size_t	i;
	size_t	j;

	j = 0;
	src_len = ms_to_strlen(s);
	if ((dest == NULL || s->cmd_pool[s->r_indx] == NULL) && size == 0)
		return (0);
	if (dest == 0 || size == 0)
		return (src_len);
	i = s->indx;
	while (s->cmd_pool[s->r_indx][i] != '\0' && j < size - 1)
	{
		dest[j] = s->cmd_pool[s->r_indx][i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (src_len);
}

size_t	ms_to_strlen(t_pool *s)
{
	size_t	i;
	size_t	len;

	i = s->indx;
	len = 0;
	while (s->cmd_pool[s->r_indx][i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

void	p_s_quote_check(t_pool *pool, size_t i)
{
	if (pool->cmd_pool[pool->r_indx][i] == '\'' && pool->d_quote == 0)
		pool->s_quote = !pool->s_quote;
	else if (pool->cmd_pool[pool->r_indx][i] == '"' && pool->s_quote == 0)
		pool->d_quote = !pool->d_quote;
}

int	j_quote_check(t_job *j)
{
	if (j->job[j->r_indx][j->indx] == '\0')
		return (1);
	else if (j->job[j->r_indx][j->indx] == '\'' && j->d_quote == 0)
	{
		j->s_quote = !j->s_quote;
		j->indx++;
		if (j->job[j->r_indx][j->indx] == '\0')
			return (1);
	}
	else if (j->job[j->r_indx][j->indx] == '"' && j->s_quote == 0)
	{
		j->d_quote = !j->d_quote;
		j->indx++;
		if (j->job[j->r_indx][j->indx] == '\0')
			return (1);
	}
	else if (j->job[j->r_indx][j->indx] == '\'' && j->d_quote == 1)
		return (0);
	else if (j->job[j->r_indx][j->indx] == '"' && j->s_quote == 1)
		return (0);
	if (j->job[j->r_indx][j->indx] == '"' || j->job[j->r_indx][j->indx] == '\'')
		j_quote_check(j);
	return (0);
}
