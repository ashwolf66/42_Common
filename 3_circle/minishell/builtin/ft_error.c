/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:14:25 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 04:14:26 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

int	err_env(int type)
{
	if (type == 1)
		printf("bash: env: No such file or directory\n");
	return (1);
}

int	err_cd(t_info *b_info, int type)
{
	if (type == 1)
		print_err("bash: cd: %s not set\n", b_info->cmd[1]);
	if (type == 2)
		print_err("bash: cd: too many arguments\n", "");
	if (type == 3)
		print_err("bash: cd: %s: No such file or directory\n", b_info->cmd[1]);
	return (1);
}

int	err_exit(t_info *b_info, int type)
{
	(void)b_info;
	(void)type;
	return (1);
}

int	err_exp(t_info *b_info, int type)
{
	int	i;

	i = 0;
	while (b_info->cmd[i])
		i++;
	if (type == 1)
		print_err("bash: export: `%s': not a valid identifier\n", \
			b_info->cmd[i - 1]);
	return (1);
}
