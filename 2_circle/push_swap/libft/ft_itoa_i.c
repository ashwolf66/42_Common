/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:09:20 by jacha             #+#    #+#             */
/*   Updated: 2024/03/02 16:08:36 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_i(int n)
{
	char	*result;
	int		len;
	int		i;
	int		mod;

	i = 0;
	if (n < 0)
		i = 1;
	len = int_len(n);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (NULL);
	result[len--] = '\0';
	while (len >= 0)
	{
		mod = n % 10;
		if (mod < 0)
			mod *= -1;
		result[len] = mod + '0';
		n /= 10;
		len--;
	}
	if (i == 1)
		result[0] = '-';
	return (result);
}
