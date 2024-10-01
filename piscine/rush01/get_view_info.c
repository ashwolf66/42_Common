/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_view_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:45:42 by jacha             #+#    #+#             */
/*   Updated: 2024/01/23 17:15:20 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	get_view_info(int info[16], char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if ('1' <= src[i] && src[i] <= ('0' + 4))
		{
			info[i / 2] = src[i] - '0';
		}
		else
			return (0);
		i++;
		if (!src[i])
			break ;
		else if (src[i] == ' ')
			i++;
		else
			return (0);
	}
	if ((i + 1) == 4 * 4 * 2)
		return (1);
	else
		return (0);
}
