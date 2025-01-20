/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:56:49 by jacha             #+#    #+#             */
/*   Updated: 2025/01/18 16:57:10 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac == 1)
	{
		mlx_start(&data);
		mlx_loop(data.mlx);
	}
	else
		exit(EXIT_FAILURE);
	return (0);
}
