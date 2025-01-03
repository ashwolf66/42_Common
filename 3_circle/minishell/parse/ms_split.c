/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:30:07 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:32:24 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

static size_t	row_len(t_pool *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s->cmd_pool[s->r_indx][i] != '\0')
	{
		p_s_quote_check(s, i);
		if (s->cmd_pool[s->r_indx][i] != c && (s->s_quote == 0
					|| s->d_quote == 0))
		{
			len++;
			while (s->cmd_pool[s->r_indx][i] != '\0'
					&& s->cmd_pool[s->r_indx][i] != c
					&& (s->s_quote == 0 || s->d_quote == 0))
			{
				i++;
				p_s_quote_check(s, i);
			}
		}
		else
			i++;
	}
	return (len);
}

static size_t	colum_len(t_pool *s, char c)
{
	size_t	i;
	size_t	len;

	i = s->indx;
	len = 0;
	while (s->cmd_pool[s->r_indx][i] != '\0')
	{
		if (s->cmd_pool[s->r_indx][i] == c && s->s_quote == 0 &&
			s->d_quote == 0)
			break ;
		i++;
		len++;
		p_s_quote_check(s, i);
	}
	return (len);
}

static char	free_mal(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

static int	cpy_contents(char **result, t_pool *s, char c)
{
	size_t	i;

	i = 0;
	while (i < s->row)
	{
		init_pool_quote(s);
		p_quote_check(s);
		while (s->cmd_pool[s->r_indx][s->indx] == c && s->s_quote == 0
				&& s->d_quote == 0)
		{
			s->indx++;
			p_quote_check(s);
		}
		s->col = colum_len(s, c);
		result[i] = (char *)ms_calloc(s->col + 1, sizeof(char));
		if (!result[i])
			return (free_mal(result));
		init_pool_quote(s);
		ms_to_strlcpy(result[i], s, s->col + 1);
		i++;
		s->indx += s->col;
	}
	result[i] = '\0';
	return (1);
}

char	**ms_split(t_pool *pool, char c)
{
	char	**result;

	result = NULL;
	if (!pool->cmd_pool[pool->r_indx])
		return (0);
	pool->row = row_len(pool, c);
	result = (char **)malloc(sizeof(char *) * (pool->row + 1));
	if (!result)
	{
		free(result);
		return (0);
	}
	init_pool_quote(pool);
	if (cpy_contents(result, pool, c) == 0)
		return (0);
	return (result);
}
