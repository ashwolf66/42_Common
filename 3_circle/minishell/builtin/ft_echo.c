/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:13:35 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 04:13:37 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	ft_echo(t_info *b_info)
{
	int	index;

	index = echo_string_check(b_info);
	if (!b_info->cmd[1])
	{
		write(1, "\n", 1);
		return (1);
	}
	while (b_info->cmd[index])
	{
		printf("%s", b_info->cmd[index]);
		if (b_info->cmd[index + 1])
			printf(" ");
		index++;
	}
	if (index > 1 && echo_string_check(b_info) == 1)
		printf("\n");
	return (1);
}

int	echo_string_check(t_info *b_info)
{
	int	locate;
	int	i;

	locate = 0;
	while (b_info->cmd[++locate])
	{
		if (b_info->cmd[locate][0] != '-')
			return (locate);
		i = 1;
		while (b_info->cmd[locate][i])
		{
			if (b_info->cmd[locate][i] != 'n')
				return (locate);
			i++;
		}
	}
	return (locate);
}
