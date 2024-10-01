/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:09:20 by jacha             #+#    #+#             */
/*   Updated: 2024/03/22 16:07:44 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	int_len(unsigned int n)
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

char	*ft_itoa_ui(unsigned int n)
{
	char	*result;
	long	len;
	long	mod;

	len = int_len(n);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == NULL)
		return (NULL);
	result[len--] = '\0';
	while (len >= 0)
	{
		mod = n % 10;
		result[len] = mod + '0';
		n /= 10;
		len--;
	}
	return (result);
}
