/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:15:00 by jacha             #+#    #+#             */
/*   Updated: 2024/02/01 19:45:10 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*range;
	int	i;

	i = 0;
	range = (int *)malloc((max - min + 1) * sizeof(int));
	if (min >= max)
	{
		range = NULL;
		return (0);
	}
	while (min < max)
	{
		range[i] = min;
		i++;
		min++;
	}
	range[i] = '\0';
	return (range);
}
