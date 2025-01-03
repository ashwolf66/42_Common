/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchin <hchin@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:16:44 by hchin             #+#    #+#             */
/*   Updated: 2024/03/01 20:16:50 by hchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_check(int n)
{
	int	num;
	int	count;

	num = n;
	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	else if (n == 0)
	{
		count = 1;
		return (count);
	}
	while (num)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static void	int_ch(char *str, size_t n, int count)
{
	count--;
	if (n >= 10)
		int_ch(str, n / 10, count);
	*(str + count) = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	int			count;
	long		num;
	char		*str;

	count = digit_check(n);
	num = n;
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		*str = '-';
		int_ch(str, num * -1, count);
	}
	else
		int_ch(str, num, count);
	*(str + count) = '\0';
	return (str);
}
/*
int main(void)
{
    char *str = ft_itoa(123);
    printf("%s", str); 
}
*/
