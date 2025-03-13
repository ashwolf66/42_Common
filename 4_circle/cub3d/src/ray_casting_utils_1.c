/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:54:54 by jacha             #+#    #+#             */
/*   Updated: 2025/03/13 13:08:11 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		ray->wall_dist = (ray->map_y - py + (1 - ray->step_y)
				/ 2.0) / ray->ray_dir_y;
	}
}

void	wall_height(t_ray *ray)
{
	ray->height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	draw_wall(t_data *data, t_ray *ray, int x)
{
	double	wall;
	int		t_num;
	int		t_x;
	int		y;
	int		texture;

	t_num = get_t_num(ray);
	if (ray->side == 0)
		wall = data->player.pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		wall = data->player.pos_x + ray->wall_dist * ray->ray_dir_x;
	wall -= floor(wall);
	t_x = (int)(wall * data->map->texture[t_num].img.width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		t_x = data->map->texture[t_num].img.width - t_x - 1;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture = get_texture(&data->map->texture[t_num].img,
				t_x, ((y - WIN_HEIGHT / 2 + ray->height / 2)
					* data->map->texture[t_num].img.height) / ray->height);
		put_pixel(&data->img, x, y, texture);
		y++;
	}
}

int	get_texture(t_img *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->addr + (y * texture->line_length
			+ x * (texture->bit_per_pixel / 8));
	return (*(unsigned int *)pixel);
}
