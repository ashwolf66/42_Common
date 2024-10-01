/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:31:13 by jacha             #+#    #+#             */
/*   Updated: 2024/03/05 21:29:20 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = malloc(num * size);
	if (temp == NULL)
	{
		free (temp);
		return (NULL);
	}
	while (i < (num * size))
	{
		temp[i] = '\0';
		i++;
	}
	return (temp);
}
