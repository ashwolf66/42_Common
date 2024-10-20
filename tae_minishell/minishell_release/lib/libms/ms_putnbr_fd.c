/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:24:28 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/08 09:44:08 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

void	ms_putnbr_fd(int n, int fd)
{
	char	temp;

	if (n < 0)
		temp = (-(n % 10)) + '0';
	else
		temp = (n % 10) + '0';
	if (n / 10 == 0)
	{
		if (n < 0)
			write(fd, "-", 1);
		write(fd, &temp, 1);
		return ;
	}
	ms_putnbr_fd(n / 10, fd);
	write(fd, &temp, 1);
}
