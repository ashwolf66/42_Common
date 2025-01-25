#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

// 키 상태를 저장할 배열 또는 플래그
int key_states[256] = {0};

// 키가 눌렸을 때의 처리
int key_press(int keycode, void *param)
{
	(void)param;
	key_states[keycode] = 1; // 키 상태를 활성화
	printf("Key %d pressed\n", keycode);
	return (0);
}

// 키가 떼어졌을 때의 처리
int key_release(int keycode, void *param)
{
	(void)param;
	key_states[keycode] = 0; // 키 상태를 비활성화
	printf("Key %d released\n", keycode);
	return (0);
}

// 지속적으로 키 상태를 확인
int loop_handler(void *param)
{
	(void)param;
	if (key_states[100]) // W 키 (예: keycode 13)
		printf("W key is being held\n");
	if (key_states[0]) // A 키 (예: keycode 0)
		printf("A key is being held\n");
	return (0);
}

int main()
{
	void *mlx;
	void *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "Key Press Example");

	// 키 이벤트 설정
	mlx_hook(win, 2, 1L << 0, key_press, NULL);	  // KeyPress 이벤트
	mlx_hook(win, 3, 1L << 1, key_release, NULL); // KeyRelease 이벤트
	mlx_loop_hook(mlx, loop_handler, NULL);		  // 메인 루프에서 처리

	mlx_loop(mlx);
	return (0);
}
