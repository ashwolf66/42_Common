#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *addr;
    int     bpp;        // bits per pixel
    int     line_len;   // line length
    int     endian;     // endian
    int     x;          // 픽셀의 현재 X좌표
    int     y;          // 픽셀의 현재 Y좌표
} t_data;

// 32x32 크기의 정사각형을 그리는 함수
void    draw_square(t_data *data, int x, int y, int color)
{
    int i, j;

    for (i = 0; i < 32; i++) // 세로 반복
    {
        for (j = 0; j < 32; j++) // 가로 반복
        {
            char *dst = data->addr + ((y + i) * data->line_len + (x + j) * (data->bpp / 8));
            *(unsigned int*)dst = color;
        }
    }
}

// 키 이벤트를 처리하는 함수
int key_event(int keycode, t_data *data)
{
    // 현재 픽셀을 지우기 (배경색으로 덮기)
    draw_square(data, data->x, data->y, 0x000000); // 검은색 배경

    // 키 입력에 따라 픽셀 이동
    if (keycode == 65361) // 왼쪽 키
        data->x -= 32;
    if (keycode == 65362) // 위쪽 키
        data->y -= 32;
    if (keycode == 65363) // 오른쪽 키
        data->x += 32;
    if (keycode == 65364) // 아래쪽 키
        data->y += 32;

    // 새로운 위치에 픽셀(32x32 정사각형) 그리기
    draw_square(data, data->x, data->y, 0x00FF0000); // 빨간색 픽셀

    // 화면 갱신
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
    return (0);
}

int main()
{
    t_data  img;

    // MiniLibX 초기화 및 윈도우 생성
    img.mlx_ptr = mlx_init();
    img.win_ptr = mlx_new_window(img.mlx_ptr, 800, 600, "Move Pixel (32x32)");

    // 이미지 생성
    img.img_ptr = mlx_new_image(img.mlx_ptr, 800, 600);
    img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);

    // 초기 픽셀 위치 설정
    img.x = 400;
    img.y = 300;

    // 초기 픽셀을 빨간색으로 그리기 (32x32 크기)
    draw_square(&img, img.x, img.y, 0x00FF0000);
    mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);

    // 키 이벤트 등록
    mlx_key_hook(img.win_ptr, key_event, &img);

    // 이벤트 루프 시작
    mlx_loop(img.mlx_ptr);
    return (0);
}