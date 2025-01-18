/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:10:10 by jacha             #+#    #+#             */
/*   Updated: 2024/05/17 18:09:56 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_charprintf_c(const char **format, va_list args, size_t *str_len)
{
	char	ch;

	if (**format == 'c')
	{
		ch = va_arg(args, int);
		(*str_len)++;
		ft_putchar_fd(ch, 1);
	}
	else if (**format == '%')
	{
		ch = '%';
		(*str_len)++;
		ft_putchar_fd(ch, 1);
	}
	(*format)++;
}

void	ft_charprintf_s(const char **format, va_list args, size_t *str_len)
{
	char	*str;

	if (**format == 's')
	{
		str = va_arg(args, char *);
		if (str == NULL)
		{
			ft_putstr_fd("(null)", 1);
			*str_len += 6;
		}
		else
		{
			*str_len += ft_strlen((const char *)str);
			ft_putstr_fd(str, 1);
		}
	}
	(*format)++;
}
