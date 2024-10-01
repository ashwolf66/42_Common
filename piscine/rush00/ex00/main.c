/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:15:04 by jacha             #+#    #+#             */
/*   Updated: 2024/01/17 18:27:53 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

extern	void	rush(int col, int row);
extern	void	ft_putchar(char c);

long	atoi(const char *S)
{
	long	num;
	int		i;

	i = 0;
	while (S[i] != '\0')
	{
		if (S[i] < '0' || S[i] > '9')
		{
			return (-1);
		}
		i++;
	}
	num = 0;
	i = 0;
	while (S[i] && (S[i] >= '0' && S[i] <= '9'))
	{
		num = num * 10 + (S[i] - '0');
		i++;
	}
	return (num);
}

int	main(int argc, char *argv[])
{
	int	a;
	int	b;

	if (argc == 3)
	{
		a = atoi(argv[1]);
		b = atoi(argv[2]);
		if (a == -1 || b == -1)
		{
			ft_putchar('D');
			return (0);
		}
		rush(a, b);
	}
	else if (argc == 1)
	{
		rush(5, 5);
	}
	else
	{
		ft_putchar('D');
	}
	return (0);
}
