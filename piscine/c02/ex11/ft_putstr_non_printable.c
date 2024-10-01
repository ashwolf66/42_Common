/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:02:01 by jacha             #+#    #+#             */
/*   Updated: 2024/01/25 20:42:22 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ascii_trans(unsigned char str)
{
	char	mod;

	write(1, "\\", 1);
	mod = 48 + (str / 16);
	write(1, &mod, 1);
	if (str % 16 < 10)
	{
		mod = 48 + (str % 16);
		write(1, &mod, 1);
	}
	else
	{
		mod = 87 + (str % 16);
		write(1, &mod, 1);
	}
}

void	ft_putstr_non_printable(char *str)
{
	unsigned int	i;
	unsigned char	ch;

	i = 0;
	while (str[i] != '\0')
	{
		ch = (unsigned char)str[i];
		if (ch > 126 || ch < 32)
		{
			ascii_trans(ch);
			i++;
			ch = (unsigned char)str[i];
		}
		write(1, &ch, 1);
		i++;
	}
}
