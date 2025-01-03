/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pool_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:01:37 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:03:25 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	ms_env_check(char *src, size_t *i, t_commend *com, t_info *b_info)
{
	com->temp = NULL;
	com->len = ms_get_env_len(src, i, com);
	if (com->s_quote == 1 || com->len == 0 || com->temp == NULL)
		return ;
	if (!ms_ps_find_list_key(b_info, com))
		com->temp[0] = '\0';
	*i += com->len + 1;
}

int	ms_get_env_len(char *str, size_t *indx, t_commend *com)
{
	int	i;
	int	len;

	len = 0;
	i = *indx + 1;
	if (str[i] == '?')
	{
		com->temp = (char *)malloc(sizeof(char) * (++len + 1));
		if (!com->temp)
			return (0);
		ms_cpy_temp(com, str, i, len);
		return (len);
	}
	if (ms_return_1(str, i))
		return (0);
	while (ms_return_2(str, i))
	{
		len++;
		i++;
	}
	i = *indx + 1;
	if (ms_utils_1(str, com, len, i) == 1)
		return (len);
	else
		return (0);
}

void	ms_cpy_temp(t_commend *com, char *str, int i, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		com->temp[j] = str[i];
		i++;
		j++;
	}
	com->temp[j] = '\0';
}

int	ms_ps_find_list_key(t_info *b_info, t_commend *cmd)
{
	t_list	*current;
	char	*str;

	if (ft_strcmp("?", cmd->temp) == 0)
	{
		str = ft_itoa(g_status);
		free(cmd->temp);
		cmd->temp = ft_strdup(str);
		free(str);
		str = NULL;
		return (1);
	}
	current = b_info->env_list;
	while (current != NULL)
	{
		if (ft_strcmp(cmd->temp, current->key) == 0)
		{
			free(cmd->temp);
			cmd->temp = ft_strdup(current->val);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
