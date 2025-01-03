/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:02:03 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 04:02:09 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	print_list(t_list *head, char *cmd)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strncmp("exp", cmd, 3) == 0)
		{
			printf("declare -x ");
			printf("%s=", current->key);
			if (current->val != NULL)
				printf("\"%s\"\n", current->val);
			else
				printf("\"\"\n");
		}
		else
		{
			while (!current->val && current->next)
				current = current->next;
			printf("%s=%s\n", current->key, current->val);
		}
		current = current->next;
	}
}

void	free_list(t_list *head)
{
	t_list	*current;
	t_list	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->key != NULL)
			free(current->key);
		if (current->val != NULL)
			free(current->val);
		free(current);
		current = next;
	}
}

int	find_list_key(t_list *head, char *find_cmd)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(find_cmd, current->key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

char	**key_val_separ(char *cmd)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * 3);
	i = 0;
	if (!result)
		return (NULL);
	while (cmd[i] && cmd[i] != '+' && cmd[i] != '=')
		i++;
	result[0] = ft_substr(cmd, 0, i);
	if (cmd[i] == '+' && cmd[i + 1] == '=')
		result[1] = ft_strdup(cmd + i + 2);
	else if (cmd[i] == '=')
		result[1] = ft_strdup(cmd + i + 1);
	else
		result[1] = NULL;
	result[2] = NULL;
	return (result);
}
