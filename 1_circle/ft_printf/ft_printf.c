/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:06:59 by jacha             #+#    #+#             */
/*   Updated: 2025/01/15 14:42:37 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_manprintf(const char **format, va_list args, size_t *str_len)
{
	if (**format == 'c' || **format == '%')
		ft_charprintf_c(format, args, str_len);
	else if (**format == 's')
		ft_charprintf_s(format, args, str_len);
	else if (**format == 'p')
		ft_hexprintf_p(format, args, str_len);
	else if (**format == 'x' || **format == 'X')
		ft_hexprintf_x(format, args, str_len);
	else if (**format == 'd' || **format == 'i' || **format == 'u')
		ft_intprintf(format, args, str_len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	str_len;

	str_len = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			ft_manprintf(&format, args, &str_len);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			str_len++;
			format++;
		}
	}
	va_end(args);
	return ((int)str_len);
}
