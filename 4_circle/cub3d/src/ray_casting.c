#include "cub3d.h"

void    cast_rays(t_data *data)
{
    int     x;
    t_ray   ray;
    double  camera_x;
    
    for (x = 0; x < NUM_RAYS; x++)
    {
        camera_x = 2 * x / (double)NUM_RAYS - 1;
        ray.ray_angle = data->player.angle + atan(camera_x * tan(FOV * (M_PI / 180.0) / 2));

        ray.delta_x = cos(ray.ray_angle);
        ray.delta_y = sin(ray.ray_angle);
        
        cast_single_ray(data, &ray, x);
    }
}

void    cast_single_ray(t_data *data, t_ray *ray, int x)
{
    int map_x = (int)(data->player.px / TILE_SIZE);
    int map_y = (int)(data->player.py / TILE_SIZE);
    
    double delta_dist_x = fabs(1 / ray->delta_x);
    double delta_dist_y = fabs(1 / ray->delta_y);
    
    if (ray->delta_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (data->player.px - map_x * TILE_SIZE) * delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (map_x * TILE_SIZE + TILE_SIZE - data->player.px) * delta_dist_x;
    }
    if (ray->delta_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (data->player.py - map_y * TILE_SIZE) * delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (map_y * TILE_SIZE + TILE_SIZE - data->player.py) * delta_dist_y;
    }

    dda_algorithm(data, ray, map_x, map_y, x);
}

void    dda_algorithm(t_data *data, t_ray *ray, int map_x, int map_y, int x)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += fabs(1 / ray->delta_x);
            map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += fabs(1 / ray->delta_y);
            map_y += ray->step_y;
            ray->side = 1;
        }
        if (data->map.cub_map[map_y][map_x] == '1') 
            ray->hit = 1;
    }
    draw_wall(data, ray, x);
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
        else                  // 서쪽 벽
            color = 0x0000FF; // 파란색
    }
    else // 수평 벽
    {
        if (ray->step_y > 0)  // 남쪽 벽
            color = 0x00FF00; // 초록색
        else                  // 북쪽 벽
            color = 0xFF0000; // 빨간색
    }

    if (ray->side == 0)
        perp_wall_dist = (ray->side_dist_x - fabs(1 / ray->delta_x));
    else
        perp_wall_dist = (ray->side_dist_y - fabs(1 / ray->delta_y));
    
    // 벽 높이 조절 (크기를 키우거나 줄일 수 있음)
    line_height = (int)((WIN_HEIGHT * 2.5) / pow(perp_wall_dist, 0.8));  

    // 최소 및 최대 크기 제한
    if (line_height < 20) line_height = 20;
    if (line_height > WIN_HEIGHT) line_height = WIN_HEIGHT;

    draw_start = -line_height / 2 + WIN_HEIGHT / 2;
    draw_end = line_height / 2 + WIN_HEIGHT / 2;

    if (draw_start < 0) draw_start = 0;
    if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;
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
