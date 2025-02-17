#include "cub3d.h"

double angle_op(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0.0)
		angle += 2.0 * M_PI;
	return (angle);
}

void w_s_move(t_data *data)
{
	if (data->player.w == 1)
	{
		data->player.px += cos(data->player.angle) * SPEED;
		data->player.py += sin(data->player.angle) * SPEED;
		if (length_check(data))
		{
			data->player.px -= cos(data->player.angle) * SPEED;
			data->player.py -= sin(data->player.angle) * SPEED;
		}
	}
	if (data->player.s == 1)
	{
		data->player.px -= cos(data->player.angle) * SPEED;
		data->player.py -= sin(data->player.angle) * SPEED;
		if (length_check(data))
		{
			data->player.px += cos(data->player.angle) * SPEED;
			data->player.py += sin(data->player.angle) * SPEED;
		}
	}
}

void a_d_move(t_data *data)
{
	if (data->player.a == 1)
	{
		data->player.px -= cos(data->player.angle + M_PI / 2.0) * SPEED;
		data->player.py -= sin(data->player.angle + M_PI / 2.0) * SPEED;
		if (length_check(data))
		{
			data->player.px += cos(data->player.angle + M_PI / 2.0) * SPEED;
			data->player.py += sin(data->player.angle + M_PI / 2.0) * SPEED;
		}
	}
	if (data->player.d == 1)
	{
		data->player.px += cos(data->player.angle + M_PI / 2.0) * SPEED;
		data->player.py += sin(data->player.angle + M_PI / 2.0) * SPEED;
		if (length_check(data))
		{
			data->player.px -= cos(data->player.angle + M_PI / 2.0) * SPEED;
			data->player.py -= sin(data->player.angle + M_PI / 2.0) * SPEED;
		}
	}
}

int length_check(t_data *data)
{
    double buffer = 10.0; // 벽과의 최소 거리 (플레이어 크기)
    int map_x, map_y;

    // 플레이어의 네 방향을 검사하여 벽 충돌 여부 확인
    for (double dx = -buffer; dx <= buffer; dx += buffer * 2)
    {
        for (double dy = -buffer; dy <= buffer; dy += buffer * 2)
        {
            map_x = (int)((data->player.px + dx) / TILE_SIZE);
            map_y = (int)((data->player.py + dy) / TILE_SIZE);

            // 맵 경계 밖으로 나가는 경우도 감지
            if (map_x < 0 || map_x >= data->map.width || map_y < 0 || map_y >= data->map.height)
                return (1); // 경계를 넘어가면 충돌로 간주

            // 플레이어가 벽('1')과 충돌하는 경우 감지
            if (data->map.cub_map[map_y][map_x] == '1')
                return (1); // 충돌 발생
        }
    }

    return (0); // 충돌 없음
}

void	move_funtion(t_data *data)
{
	if (data->player.w == 1 || data->player.s == 1)
		w_s_move(data);
	if (data->player.a == 1 || data->player.d == 1)
		a_d_move(data);
	if (data->player.left == 1)
		data->player.angle = angle_op(data->player.angle - ANGLE_CHANGE);
	if (data->player.right == 1)
		data->player.angle = angle_op(data->player.angle + ANGLE_CHANGE);
}
