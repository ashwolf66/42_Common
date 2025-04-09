NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include -I./libft -I./minilibx-linux
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm -lX11 -lXext
SRCS =	src/main.c \
		src/argv_check.c \
		src/init_map.c \
		src/init_map_2.c \
		src/init_map_3.c \
		src/free.c \
		src/free_2.c \
		src/init.c \
		src/init_2.c \
		src/map_check.c \
		src/map_check_2.c \
		src/mlx_event.c \
		src/mlx_start.c \
		src/move_handle.c \
		src/move_handle_utils.c \
		src/parse_map.c \
		src/parse_map_2.c \
		src/ray_casting.c \
		src/ray_casting_utils_1.c \
		src/ray_casting_utils_2.c \
		src/set_tex_col.c \
		src/texture_set.c
# SRCS = src/test2.c
# SRCS = src/test_img_pixel.c
OBJS = $(SRCS:.c=.o)

all: $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a $(NAME)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -g

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re