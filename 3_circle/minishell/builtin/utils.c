/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 03:52:51 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 03:52:53 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

char	*exp_val(char **key)
{
	int		i;
	char	*res;
	char	*temp;

	i = 0;
	if (key[0] == NULL)
		return (NULL);
	res = ft_strdup(key[0]);
	while (key[++i] != NULL)
	{
		temp = res;
		res = ft_strjoin(res, "=");
		free(temp);
		temp = res;
		res = ft_strjoin(res, key[i]);
		free(temp);
	}
	return (res);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_putstr(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
		write(1, &s[i], 1);
	return ;
}

void	print_err(char *e_mess, char *str)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (e_mess[++i])
	{
		if (e_mess[i] == '%' && e_mess[i + 1] == 's')
		{
			i++;
			while (str[++j])
				write(1, &str[j], 1);
		}
		else
			write(1, &e_mess[i], 1);
	}
}
