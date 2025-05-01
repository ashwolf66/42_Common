/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:53:59 by jacha             #+#    #+#             */
/*   Updated: 2025/05/01 16:26:55 by hyeyeom          ###   ########.fr       */
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

# define WIN_WIDTH 854
# define WIN_HEIGHT 480
# define K_ESC 65307
# define K_W 119
# define K_S 115
# define K_A 97
# define K_D 100
# define K_LEFT 65361
# define K_RIGHT 65363
# define TILE_SIZE 64
# define SPEED 0.005
# define ANG_SPEED 0.0035
# define FOV 60.0

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_color
{
	int	color;
}	t_color;

typedef struct s_texture
{
	char	*path;
	t_img	img;
}	t_texture;

typedef struct s_map
{
	t_texture		texture[4];
	t_color			floor;
	t_color			ceiling;
	char			**cub_map;
	int				height;
	int				width;
	int				flage;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	pla_x;
	double	pla_y;
	int		w;
	int		s;
	int		a;
	int		d;
	int		left;
	int		right;
}	t_player;

typedef struct s_ray
{
	double	camera;
	double	ray_angle;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_x;
	double	delta_y;
	double	side_dist_x;
	double	side_dist_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
	int		height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_img		img;
	t_player	player;
}	t_data;

// main
int		refresh_map(t_data *data);
void	fill_background(t_data *data);
void	print_error(t_data *data);

// argv_check
int		argv_check(int ac, char *map_file);
int		extension_check(char *map_file, char *cub);
int		file_check(char *map_file);

// init_map
t_map	*init_map(char *map_file);
int		operation_map_file(t_map *map, int fd);
int		read_file(int fd, int *size, char ***lines, t_map *map);
int		operation_cub_map(char ***lines, t_map *map);
int		operation_line(char *line, int *size, char ***lines, t_map *map);
int		check_t_c(t_map *map);
int		set_t_c(char *line, t_map *map);
int		set_cub_map(char *line, int *size, char ***lines);
void	operation_line_end_space(char **line);
void	operation_line_start_space(char **line);
void	operation_line_space_color(char **line);

// map_check
int		cub_map_validate(t_map *map);
int		cub_map_validate_check(t_map *map);
int		wall_check(int i, int j, t_map *map);
int		cub_map_check(t_map *map);
int		player_check(t_map *map);

// parse_map
int		parse_cub_map(char **lines, t_map *map);
int		check_map_height(char **lines);
int		check_map_width(char **lines);
char	**create_cub_map(char **lines, t_map *map);
int		init_row(char **temp, int i, t_map *map);

// set_tex_col
int		set_texture(char *line, t_map *map, int direct);
int		set_color(char *line, t_color *color, t_map *map, char chr);
int		alloc_color(char **colors, t_color *color, t_map *map);

// free
void	free_data(t_data *data);
void	free_map(t_map *map);
void	free_cub_map(t_map *map);
void	free_texture(t_map *map);
void	free_double(char **temp);
void	free_mlx_data(t_data *data);
void	free_gnl(t_gnl *gnl);

// mlx_start
int		mlx_start(t_data *data, t_map *map);

// texture_set
int		texture_set(t_data *data);
int		single_texture_set(t_data *data, int i);

// init
void	key_init(t_data *data);
void	player_init(t_data *data);
void	player_vector(t_player *player, char dir);
void	camera_plane(t_player *player, char dir);
void	init_texture(t_map *map);
void	init_map_av(t_map *map);

// mlx_event
void	event_handle(t_data *data);
int		close_handler(t_data *data);
int		key_press(int keysym, t_data *data);
int		key_release(int keysym, t_data *data);

// move_handle
void	angle_op(t_data *data, double num);
void	w_s_move(t_data *data);
void	a_d_move(t_data *data);
void	move_funtion(t_data *data);

// move_handle_utils
int		length_check(t_data *data);

// ray_casting
void	cast_rays(t_data *data);
void	init_ray(t_data *data, t_ray *ray, int x);
void	calculate(t_data *data, t_ray *ray);
void	dda_algorithm(t_data *data, t_ray *ray);

// ray_casting_utils_1
void	calculate_wall(t_data *data, t_ray *ray);
void	wall_height(t_ray *ray);
void	draw_wall(t_data *data, t_ray *ray, int x);
int		get_texture(t_img *texture, int x, int y);
double	set_wall_side(double wall, t_data *data, t_ray *ray);

// ray_casting_utils_2
void	put_pixel(t_img *img, int x, int y, unsigned int color);
int		get_t_num(t_ray *ray);

#endif
