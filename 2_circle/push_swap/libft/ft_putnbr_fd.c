/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:37:02 by jacha             #+#    #+#             */
/*   Updated: 2024/03/02 18:28:07 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		div;
	int		mod;
	char	nbr;

	div = n / 10;
	mod = n % 10;
	if (div != 0)
		ft_putnbr_fd(div, fd);
	if (mod < 0)
		mod *= -1;
	if (div == 0 && n < 0)
		write(fd, "-", 1);
	nbr = mod + '0';
	write(fd, &nbr, 1);
}
