/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:21:52 by hchin             #+#    #+#             */
/*   Updated: 2024/02/27 16:29:29 by hchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	point;
	int				i;

	point = c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == point)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == point)
		return ((char *)s);
	return (0);
}
