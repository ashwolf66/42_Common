/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:06:15 by jacha             #+#    #+#             */
/*   Updated: 2024/03/06 21:25:17 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	point(char *s1, char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (((char *)s1)[i] != '\0')
	{
		while (((char *)set)[j] != '\0')
		{
			if (((char *)s1)[i] == ((char *)set)[j])
				break ;
			j++;
		}
		if (((char *)set)[j] == '\0')
		{
			break ;
		}
		j = 0;
		i++;
	}
	return (i);
}

static int	r_point(char *s1, char *set, int i)
{
	int	j;

	j = 0;
	while (i >= 0)
	{
		while (((char *)set)[j] != '\0')
		{
			if (((char *)s1)[i] == ((char *)set)[j])
				break ;
			j++;
		}
		if (((char *)set)[j] == '\0')
		{
			break ;
		}
		j = 0;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	int		s1_len;
	int		start;
	int		end;

	if (!s1)
		return (0);
	s1_len = ft_strlen((const char *)s1);
	start = point ((char *)s1, (char *)set);
	end = r_point ((char *)s1, (char *)set, s1_len - 1);
	if (((char *)s1)[start] == '\0')
		start = 0;
	temp = (char *)malloc(sizeof(char) * ((end - start + 1) + 1));
	if (temp == NULL)
		return (0);
	ft_strlcpy(temp, &(((const char *)s1)[start]), ((end - start + 1) + 1));
	return (temp);
}
