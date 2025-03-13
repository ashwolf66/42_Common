#include "cub3d.h"

void put_pixel(t_img *img, int x, int y, int texture)
{
	unsigned int *dst;

	*dst = texture;
	dst = (unsigned int *)(img->addr + (y * img->line_length + x * (img->bit_per_pixel / 8)));
}

int get_t_num(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (3);
		return (2);
	}
	if (ray->ray_dir_y > 0)
		return (1);
	return (0);
}