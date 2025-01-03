NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include -I./libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

SRCS =	main.c \
		parse/cmd_pool_utils_2.c \
		parse/cmd_pool_utils_3.c \
		parse/cmd_pool_utils_4.c \
		parse/cmd_pool_utils.c \
		parse/cmd_pool.c \
		parse/dr_case.c \
		parse/dr_case2.c \
		parse/execve_start.c \
		parse/find_path.c \
		parse/free.c \
		parse/init_2.c \
		parse/init.c \
		parse/ms_calloc.c \
		parse/ms_lstadd_back.c \
		parse/ms_lstnew.c \
		parse/ms_memset.c \
		parse/ms_split.c \
		parse/ms_strdup.c \
		parse/not_one_job.c \
		parse/one_job.c \
		parse/parse_2.c \
		parse/parse.c \
		parse/remove_quote.c \
		parse/signal_2.c \
		parse/signal.c \
		parse/syntax_check.c \
		parse/tokenizer.c \
		parse/update_fd.c \
		parse/utils_1.c \
		parse/utils_2.c \
		parse/utils_3.c \
		parse/utils_4.c \
		builtin/ft_cd_utils.c \
		builtin/ft_cd.c \
		builtin/ft_echo.c \
		builtin/ft_env.c \
		builtin/ft_exit.c \
		builtin/ft_error.c \
		builtin/ft_export_utils.c \
		builtin/ft_export.c \
		builtin/ft_pwd.c \
		builtin/ft_unset.c \
		builtin/linked_list_utils.c \
		builtin/linked_list.c \
		builtin/par_list.c \
		builtin/utils.c \

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -g

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
