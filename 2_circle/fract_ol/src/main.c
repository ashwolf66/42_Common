/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:38:35 by jacha             #+#    #+#             */
/*   Updated: 2024/07/28 09:38:36 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10)) || \
			(argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		data.title = argv[1];
		if (!ft_strncmp(data.title, "julia", 5))
		{
			data.julia_x = ft_atodb(argv[2]);
			data.julia_y = ft_atodb(argv[3]);
		}
		data_init(&data);
		data_render(&data);
		mlx_loop(data.mlx);
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}
