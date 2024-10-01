/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:16:14 by jacha             #+#    #+#             */
/*   Updated: 2024/03/05 22:31:31 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (!len)
		return (0);
	while (((char *)big)[i] != '\0' && i < len)
	{
		j = 0;
		while (((char *)big)[i + j] == ((char *)little)[j] && (i + j) < len)
		{
			j++;
			if (((char *)little)[j] == '\0')
				return (((char *)big) + i);
		}
		i++;
	}
	return (0);
}
