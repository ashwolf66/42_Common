/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:51:16 by jacha             #+#    #+#             */
/*   Updated: 2024/03/03 14:39:50 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(s);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (temp == NULL)
		return (0);
	while (((char *)s)[i] != '\0')
	{
		temp[i] = ((char *)s)[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
