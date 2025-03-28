/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:54:52 by jacha             #+#    #+#             */
/*   Updated: 2025/03/28 14:31:05 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_rays(t_data *data)
{
	int		x;
	t_ray	ray;

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

void	dda_algorithm(t_data *data, t_ray *ray)
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
		if (ray->map_x < 0 || ray->map_x >= data->map->width
			|| ray->map_y < 0 || ray->map_y >= data->map->height)
		{
			ray->hit = 1;
			return ;
		}
		if (data->map->cub_map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
