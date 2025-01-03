/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:44:37 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:46:49 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	pipe_count_mal(t_commend *com, t_pool *pool)
{
	while (com->cmd[com->indx])
	{
		if (com->cmd[com->indx] == '|'
			&& com->s_quote == 0 && com->d_quote == 0)
			com->pipe_count++;
		c_quote_check(com);
		com->indx++;
	}
	pool->cmd_pool = (char **)malloc(sizeof(char *) * (com->pipe_count + 2));
	pool->count_temp = com->pipe_count + 2;
	pool->count = com->pipe_count;
	if (!pool->cmd_pool)
	{
		free(pool);
		perror("malloc failed");
		return (1);
	}
	init_commend(com);
	return (0);
}

int	add_cmd_pool(t_commend *com, t_pool *pool, t_info *b_info)
{
	if (!(com->cmd[com->indx]))
	{
		cmd_pipe_mal(com, pool, b_info);
		pool->cmd_pool[pool->indx] = '\0';
		free(com->cmd);
		com->cmd = NULL;
		free(com);
		return (0);
	}
	if (com->cmd[com->indx] == '|' && com->s_quote == 0 && com->d_quote == 0)
	{
		if (cmd_pipe_mal(com, pool, b_info))
			return (1);
		com->count = 0;
		com->len = 0;
		com->indx_start = com->indx + 1;
		com->indx++;
	}
	else if (direct_case(com) || un_direct_case(com))
		com->count++;
	if (com->cmd[com->indx] == '$')
		env_check(com, b_info);
	add_c_quote_check(com, pool, b_info);
	add_cmd_pool(com, pool, b_info);
	return (0);
}

int	cmd_pipe_mal(t_commend *com, t_pool *pool, t_info *b_info)
{
	if (pool->indx > pool->count_temp)
	{
		free_mem(pool->cmd_pool);
		pool->cmd_pool = NULL;
		free(pool);
		return (1);
	}
	com->size = com->count + com->temp_len + 1;
	pool->cmd_pool[pool->indx] = (char *)malloc(sizeof(char) * com->size);
	if (!pool->cmd_pool[pool->indx])
	{
		free_mem(pool->cmd_pool);
		pool->cmd_pool = NULL;
		free(pool);
		perror("malloc failed");
		return (1);
	}
	ms_strlcpy(pool->cmd_pool[pool->indx],
		&com->cmd[com->indx_start], com, b_info);
	pool->indx++;
	return (0);
}

void	ms_strlcpy(char *dest, char *src, t_commend *com, t_info *b_info)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0' && j < com->size - 1)
	{
		if (src[i] == '$' && com->s_quote == 0)
		{
			ms_env_check(src, &i, com, b_info);
			if (com->temp == NULL)
			{
				i += com->len + 2;
				continue ;
			}
			cpy_env(dest, &j, com);
			continue ;
		}
		ms_strlcpy_2(src, dest, &i, &j);
		ms_c_quote_check(src, i, com);
		ms_strlcpy_3(src, dest, &i, &j);
	}
	dest[j] = '\0';
}

void	cpy_env(char *dest, size_t *j, t_commend *com)
{
	size_t	i;

	i = 0;
	if (com->temp[0] == '\0')
	{
		free(com->temp);
		return ;
	}
	while (com->temp[i])
	{
		dest[*j] = com->temp[i];
		(*j)++;
		i++;
	}
	free(com->temp);
}
