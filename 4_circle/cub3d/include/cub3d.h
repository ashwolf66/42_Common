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
#define CUB3D_H
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

#define WIN_WIDTH 854
#define WIN_HEIGHT 480
#define K_ESC 65307
#define K_W 119
#define K_S 115
#define K_A 97
#define K_D 100
#define K_LEFT 65361
#define K_RIGHT 65363
#define TILE_SIZE 64
#define SPEED 0.5
#define ANGLE_CHANGE 0.25 * (M_PI / 180.0)
#define FOV 60.0
#define NUM_RAYS WIN_WIDTH

typedef struct s_img
{
	void *img;
	char *addr;
	int bit_per_pixel;
	int line_length;
	int endian;
	int	width;
	int	height;
} t_img;

typedef struct s_texture
{
	char	*path;
	t_img	img;
}	t_texture;

typedef struct s_map
{
	t_texture	texture[4];
	unsigned int floor;
	unsigned int ceiling;
	int height;
	int width;
	char **cub_map;
} t_map;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double pla_x;
	double pla_y;
	double angle;
	int w;
	int s;
	int a;
	int d;
	int left;
	int right;
} t_player;

typedef struct s_ray
{
	double camera;
	double ray_angle;
	double ray_dir_x;
	double ray_dir_y;
	double delta_x;
	double delta_y;
	double side_dist_x;
	double side_dist_y;
	double wall_dist;
	int step_x;
	int step_y;
	int map_x;
	int map_y;
	int hit;
	int side;
	int	height;
	int	draw_start;
	int	draw_end;
} t_ray;

typedef struct s_data
{
	void *mlx;
	void *win;
	t_map *map;
	t_img img;
	t_player player;
} t_data;

// main
int refresh_map(t_data *data);
void fill_background(t_data *data);

// mlx_start
void mlx_start(t_data *data);
void player_init(t_data *data);
void map_init(t_data *data);

// mlx_event
void event_handle(t_data *data);
int close_handler(t_data *data);
int key_press(int keysym, t_data *data);
int key_release(int keysym, t_data *data);

// move_handle
double angle_op(double angle);
void w_s_move(t_data *data);
void a_d_move(t_data *data);
int length_check(t_data *data);
void move_funtion(t_data *data);

// Raycasting
void cast_rays(t_data *data);
void cast_single_ray(t_data *data, t_ray *ray, int x);
void init_ray(t_data *data, t_ray *ray, int x);
void calculate(t_data *data, t_ray *ray);
void dda_algorithm(t_data *data, t_ray *ray);

#endif
