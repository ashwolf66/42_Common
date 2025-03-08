#include "cub3d.h"

void cast_rays(t_data *data)
{
	int x;
	t_ray ray;

	x = 0;
	while (x < NUM_RAYS)
	{
		init_ray(data, &ray, x);
		calculate(data, &ray);
		dda_algorithm(data, &ray);
		x++;
	}
}

void	init_ray(t_data *data, t_ray *ray, int x)
{
	double	dir_x;
	double	dir_y;

	ray->camera = 2.0 * (double)x / NUM_RAYS - 1.0;
	ray->ray_dir_x = data->player.dir_x + data->player.pla_x * ray->camera;
	ray->ray_dir_y = data->player.dir_y + data->player.pla_y * ray->camera;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	dir_x = 1.0 / ray->ray_dir_x;
	dir_y = 1.0 / ray->ray_dir_y;
	ray->delta_x = fabs(dir_x);
	ray->delta_y = fabs(dir_y);
	ray->hit = 0;
}

void	calculate(t_data *data, t_ray *ray)
{
	double	px;
	double	py;

	px = data->player.pos_x;
	py = data->player.pos_y;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (px - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - px) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (py - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - py) * ray->delta_y;
	}
}

void dda_algorithm(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += fabs(1 / ray->delta_x);
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += fabs(1 / ray->delta_y);
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map.cub_map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void draw_wall(t_data *data, t_ray *ray, int x)
{
	double perp_wall_dist;
	int line_height;
	int draw_start, draw_end;
	int color;

	if (ray->side == 0) // 수직 벽
	{
		if (ray->step_x > 0)  // 동쪽 벽
			color = 0xFFAA00; // 주황색
		else				  // 서쪽 벽
			color = 0x0000FF; // 파란색
	}
	else // 수평 벽
	{
		if (ray->step_y > 0)  // 남쪽 벽
			color = 0x00FF00; // 초록색
		else				  // 북쪽 벽
			color = 0xFF0000; // 빨간색
	}

	if (ray->side == 0)
		perp_wall_dist = (ray->side_dist_x - fabs(1 / ray->delta_x));
	else
		perp_wall_dist = (ray->side_dist_y - fabs(1 / ray->delta_y));

	// 벽 높이 조절 (크기를 키우거나 줄일 수 있음)
	line_height = (int)((WIN_HEIGHT * 2.5) / pow(perp_wall_dist, 0.8));

	// 최소 및 최대 크기 제한
	if (line_height < 20)
		line_height = 20;
	if (line_height > WIN_HEIGHT)
		line_height = WIN_HEIGHT;

	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	draw_vertical_line(data, x, draw_start, draw_end, color);
}

void draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	int y;
	char *dst;

	for (y = start; y < end; y++)
	{
		dst = data->img.addr + (y * data->img.line_length + x * (data->img.bit_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
