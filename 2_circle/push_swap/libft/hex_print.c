/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:12:21 by jacha             #+#    #+#             */
/*   Updated: 2024/05/17 18:10:12 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hexprintf_x(const char **format, va_list args, size_t *str_len)
{
	if (**format == 'x')
	{
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", str_len);
	}
	else if (**format == 'X')
	{
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", str_len);
	}
	(*format)++;
}

void	ft_hexprintf_p(const char **format, va_list args, size_t *str_len)
{
	char				*hex;
	unsigned long long	p;

	if (**format == 'p')
	{
		p = va_arg(args, unsigned long long);
		if (p == 0)
		{
			ft_putstr_fd("(nil)", 1);
			*str_len += 5;
		}
		else
		{
			hex = "0x";
			*str_len += 2;
			ft_putstr_fd(hex, 1);
			ft_putnbr_base(p, "0123456789abcdef", str_len);
		}
	}
	(*format)++;
}
