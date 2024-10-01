/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:11:29 by jacha             #+#    #+#             */
/*   Updated: 2024/05/17 18:09:48 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_intprintf(const char **format, va_list args, size_t *str_len)
{
	char	*num;

	if (**format == 'd')
	{
		num = ft_itoa_i(va_arg(args, int));
		*str_len += ft_strlen((const char *)num);
		ft_putstr_fd(num, 1);
		free(num);
	}
	else if (**format == 'i')
	{
		num = ft_itoa_i(va_arg(args, int));
		*str_len += ft_strlen((const char *)num);
		ft_putstr_fd(num, 1);
		free(num);
	}
	else if (**format == 'u')
	{
		num = ft_itoa_ui(va_arg(args, unsigned int));
		*str_len += ft_strlen((const char *)num);
		ft_putstr_fd(num, 1);
		free(num);
	}
	(*format)++;
}
