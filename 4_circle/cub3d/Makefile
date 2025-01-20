NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include -I./libft -I./minilibx-linux
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm -lX11 -lXext
SRCS =	src/main.c \
		src/mlx_start.c \
		src/mlx_event.c
OBJS = $(SRCS:.c=.o)

all: $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a $(NAME)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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