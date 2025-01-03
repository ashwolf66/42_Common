/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dr_case2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:37:43 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:39:31 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

char	*find_env(char *str, t_info *b_info)
{
	int		i;
	int		j;
	char	*temp;
	char	*env;
	char	*result;

	i = 0;
	j = 0;
	temp = (char *)malloc(sizeof(char) * 1024);
	if (!temp)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			env = env_len(str, &i, b_info);
			cpy_env_val(temp, env, &j);
		}
		else
			temp[j++] = str[i++];
	}
	temp[j] = '\0';
	result = ft_strdup(temp);
	free(temp);
	return (result);
}

char	*env_len(char *str, int *i, t_info *b_info)
{
	char	*temp;
	int		len;

	len = 0;
	(*i)++;
	if ((str[*i + len] < 'A' || str[*i + len] > 'Z') && (str[*i + len] < 'a'
			|| str[*i + len] > 'z') && str[*i + len] != '_')
		return (NULL);
	while ((str[*i + len] >= 'A' && str[*i + len] <= 'Z')
		|| (str[*i + len] >= 'a' && str[*i + len] <= 'z')
		|| str[*i + len] == '_' || (str[*i + len] >= '0'
			&& str[*i + len] <= '9'))
		len++;
	temp = ft_substr(str, *i, len);
	if (!temp)
		return (NULL);
	*i += len;
	return (hd_find_list_key(b_info->exp_list, temp));
}

char	*hd_find_list_key(t_list *head, char *temp)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(temp, current->key) == 0)
		{
			free(temp);
			temp = ft_strdup(current->val);
			return (temp);
		}
		current = current->next;
	}
	free(temp);
	return (ft_strdup(""));
}

void	cpy_env_val(char *temp, char *env, int *j)
{
	int	indx;

	indx = 0;
	while (env[indx])
	{
		temp[*j] = env[indx];
		(*j)++;
		indx++;
	}
	temp[*j] = '\0';
	free(env);
}

int	end_check(char *name, char *str, size_t len)
{
	if (!str)
		return (1);
	if (len == ft_strlen(name) && ft_strncmp(name, str, ft_strlen(name)) == 0)
	{
		free(str);
		return (1);
	}
	return (0);
}
