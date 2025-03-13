#include "cub3d.h"

void textur_init(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		data->map->texture[i].path = NULL;
		data->map->texture[i].img.img = NULL;
		data->map->texture[i].img.addr = NULL;
		data->map->texture[i].img.bit_per_pixel = 0;
		data->map->texture[i].img.line_length = 0;
		data->map->texture[i].img.endian = 0;
		data->map->texture[i].img.width = 0;
		data->map->texture[i].img.height = 0;
		i++;
	}
}

void key_init(t_data *data)
{
	data->player.w = 0;
	data->player.s = 0;
	data->player.a = 0;
	data->player.d = 0;
	data->player.left = 0;
	data->player.right = 0;
}

void player_init(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			if (data->map->cub_map[i][j] == 'N' ||
				data->map->cub_map[i][j] == 'S' ||
				data->map->cub_map[i][j] == 'E' ||
				data->map->cub_map[i][j] == 'W')
			{
				data->player.pos_x = (double)i + 0.5;
				data->player.pos_y = (double)j + 0.5;
				player_vextor(&data->player, data->map->cub_map[i][j]);
				camere_plane(&data->player, data->map->cub_map[i][j]);
			}
		}
		i++;
	}
}

void map_init(t_data *data)
{
	static char *map_data[] = {
		"11111111",
		"10000001",
		"10N00101",
		"10000001",
		"11111111"};

	data->map->cub_map = map_data;
	data->map->width = 8;
	data->map->height = 5;
	data->map->floor = 0xFFFFFF;
	data->map->ceiling = 0x00A0A0;
}