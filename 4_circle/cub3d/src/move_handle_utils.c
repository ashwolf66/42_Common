#include "cub3d.h"

int length_check(t_data *data)
{
	if (data->map->cub_map[(int)data->player.pos_y][(int)data->player.pos_x] != '1')
	{
		return (1);
	}
	return (0);
}