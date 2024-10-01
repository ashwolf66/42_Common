/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 01:44:08 by jacha             #+#    #+#             */
/*   Updated: 2024/02/04 02:54:48 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	str_add(char **str, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		*str[i] = src[j];
		i++;
		j++;
	}
	*str[i] = '\0';
}

int	su_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	to_len(int size, char **strs, char *sep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < size)
	{
		len += su_len(strs[i]);
		i++;
	}
	len += su_len(sep) * (size - 1);
	return (len + 1);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		i;
	int		len;
	char	*str;

	if (size == 0)
	{
		str = (char *)malloc(sizeof(char));
		if (str == 0)
			return (0);
		str[0] = '\0';
		return (str);
	}
	len = to_len(size, strs, sep);
	str = (char *)malloc(len * sizeof(char));
	if (str == 0)
		return (0);
	str[0] = 0;
	while (i < size)
	{
		str_add(&str, strs[i]);
		while (i < size - 1)
			str_add(&str, sep);
		i++;
	}
	return (str);
}
