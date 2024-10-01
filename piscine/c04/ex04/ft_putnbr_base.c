/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:16:21 by jacha             #+#    #+#             */
/*   Updated: 2024/02/03 19:13:55 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	write_nbr(int nbr, int num, char *base)
{
	int	div;
	int	mod;

	div = nbr / num;
	mod = nbr % num;
	if (div != 0)
		write_nbr(div, num, base);
	if (mod < 0)
		mod *= -1;
	if (div == 0 && nbr < 0)
		write(1, "-", 1);
	write(1, &base[mod], 1);
}

int	base_check(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i] != '\0')
	{
		j = i + 1;
		if (base[i] == '+' || base[i] == '-')
			return (-1);
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (-1);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (-1);
	return (i);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	num;

	num = base_check(base);
	if (num == -1)
		return ;
	write_nbr(nbr, num, base);
}
