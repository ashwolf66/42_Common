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
		calculate_wall(data, &ray);
		wall_height(&ray);
		draw_wall(data, &ray, x);
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
		if (data->map->cub_map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall(t_data *data, t_ray *ray)
{
	double	px;
	double	py;

	px = data->player.pos_x;
	py = data->player.pos_y;
	if (ray->side == 0)
	{
		ray->wall_dist = (ray->map_x - px + (1 - ray->step_x) / 2.0)
			/ ray->ray_dir_x;
	}
	else
	{
		ray->wall_dist = (ray->map_y - py + (1 - ray->step_y) / 2.0)
			/ ray->ray_dir_y;
	}
}

void	compute_wall_height(t_ray *ray)
{
	ray->height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void draw_wall(t_data *data, t_ray *ray, int x)
{
	double wall;
	int t_num;
	int t_x;
	int	y;
	unsigned int color;

	t_num = get_t_num(ray);
	if (ray->side == 0) // 수직 벽
		wall = data->player.pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		wall = data->player.pos_x + ray->wall_dist * ray->ray_dir_x;
	wall -= floor(wall);
	t_x = (int)(wall * data->map->texture[t_num].img.width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || \
		(ray->side == 1 && ray->ray_dir_y < 0))
		t_x = data->map->texture[t_num].img.width - t_x - 1;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		color = get_color(&data->map->texture[t_num].img, \
			t_x, ((y - WIN_HEIGHT / 2 + ray->height / 2) * \
			data->map->texture[t_num].img.height) / ray->height);
		put_pixel(&data->img, x, y, color);
		y++;
	}
}

int	get_color(t_img *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->addr + (y * texture->line_length + \
		x * (texture->bit_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	unsigned int	*dst;

	dst = (unsigned int *)(img->addr + (y * img->line_length + x
				* (img->bit_per_pixel / 8)));
	*dst = color;
}
