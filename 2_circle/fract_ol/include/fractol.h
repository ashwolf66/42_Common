/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:40:14 by jacha             #+#    #+#             */
/*   Updated: 2024/07/28 09:44:26 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define WIDTH 1000
# define HEIGHT 1000

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

# define MAGENTA_BURST 0xFF00FF
# define LIME_SHOCK 0xCCFF00
# define NEON_ORANGE 0xFF6600
# define PSYCHEDELIC_PURPLE 0x660066
# define AQUA_DREAM 0x33CCCC
# define HOT_PINK 0xFF66B2
# define ELECTRIC_BLUE 0x0066FF
# define LAVA_RED 0xFF3300

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_img
{
	void	*img;
	char	*pixel;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	*title;
	t_img	img;
	double	escape_value;
	int		iteration;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}	t_data;

void			data_init(t_data *data);
void			data_render(t_data *data);
double			map(double unscaled_num, double new_min, \
		double new_max, double old_max);
t_complex		sum_complex(t_complex z1, t_complex z2);
t_complex		square_complex(t_complex z);
int				key_handler(int keysys, t_data *data);
int				close_handler(t_data *data);
int				mouse_handler(int buttom, int x, int y, t_data *data);
int				case_jul(int x, int y, t_data *data);

#endif
