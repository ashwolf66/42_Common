/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:34:19 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 08:34:25 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	*ms_calloc(size_t num, size_t size)
{
	char	*temp;

	temp = malloc(num * size);
	if (temp == NULL)
		return (NULL);
	ms_memset(temp, 0, num * size);
	return (temp);
}
