/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:16:21 by jacha             #+#    #+#             */
/*   Updated: 2024/05/17 18:10:03 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_nbr(unsigned long long nbr, char *base, size_t *str_len)
{
	unsigned long long	div;
	unsigned long long	mod;

	div = nbr / 16;
	mod = nbr % 16;
	if (div != 0)
		write_nbr(div, base, str_len);
	write(1, &base[mod], 1);
	(*str_len)++;
}

void	ft_putnbr_base(unsigned long long nbr, char *base, size_t *str_len)
{
	write_nbr(nbr, base, str_len);
}
