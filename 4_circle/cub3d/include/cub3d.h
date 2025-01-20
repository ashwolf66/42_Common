/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:53:59 by jacha             #+#    #+#             */
/*   Updated: 2025/01/18 16:55:01 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIDTH 854
# define HEIGHT 480

typedef struct s_img	t_img;
typedef struct s_data	t_data;

struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
};
struct s_img
{
	void	*img;
	char	*arr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
};

void	mlx_start(t_data *data);

void	event_init(t_data *data);
int		close_handler(t_data *data);
int		key_handler(int keysym, t_data *data);

#endif
