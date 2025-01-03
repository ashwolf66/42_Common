/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:29:09 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:29:48 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

size_t	dup_row_len(char **s)
{
	size_t	len;

	len = 0;
	while (s[len] != NULL)
	{
		if (s[len][0] == '\0')
			break ;
		len++;
	}
	return (len);
}

size_t	dup_colum_len(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	dup_cpy(char *temp, char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
}

char	**ms_strdup(char **s)
{
	size_t	row_len;
	size_t	row;
	size_t	col_len;
	char	**temp;

	row = dup_row_len(s);
	temp = (char **)malloc(sizeof(char *) * (row + 1));
	if (temp == NULL)
		return (0);
	row_len = 0;
	while (row_len < row)
	{
		col_len = dup_colum_len(s[row_len]);
		temp[row_len] = (char *)malloc(sizeof(char) * (col_len + 1));
		if (temp[row_len] == NULL)
		{
			free_mem(temp);
			temp = NULL;
			return (0);
		}
		dup_cpy(temp[row_len], s[row_len]);
		row_len++;
	}
	temp[row_len] = '\0';
	return (temp);
}
