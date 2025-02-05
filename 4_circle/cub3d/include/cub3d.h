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

# define WIN_WIDTH		854
# define WIN_HEIGHT		480
# define K_ESC			65307
# define K_W			119
# define K_S			115
# define K_A			97
# define K_D			100
# define K_LEFT			65361
# define K_RIGHT		65363
# define TILE_SIZE		64
# define SPEED			5.0f
# define ANGLE_CHANGE	5.0f * ((float)M_PI / 180.0f)

/*
119		=	"w"
97		=	"a"
115		=	"s"
100		=	"d"
65361	=	"LEFT"
65362	=	"UP"
65363	=	"RIGHT"
65364	=	"DOWN"
*/

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_player
{
	float	px;
	float	py;
	float	angle;
	int		key;
}	t_player;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
}	t_data;

void	mlx_start(t_data *data);
void	player_init(t_player *player);
int refresh_map(t_data *data);
float angle_op(float angle);

void	event_handle(t_data *data);
int		close_handler(t_data *data);
int		key_press(int keysym, t_data *data);
int		key_release(int keysym, t_data *data);
void    draw_square(t_data *data, int x, int y, int color);

#endif
