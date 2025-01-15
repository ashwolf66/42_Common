/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:45:03 by jacha             #+#    #+#             */
/*   Updated: 2024/03/13 19:19:15 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	ft_charprintf_c(const char **format, va_list args, size_t *str_len);
void	ft_charprintf_s(const char **format, va_list args, size_t *str_len);
void	ft_intprintf(const char **format, va_list args, size_t *str_len);
void	ft_hexprintf_x(const char **format, va_list args, size_t *str_len);
void	ft_hexprintf_p(const char **format, va_list args, size_t *str_len);
void	ft_putnbr_base(unsigned long long nbr, char *base, size_t *str_len);

#endif