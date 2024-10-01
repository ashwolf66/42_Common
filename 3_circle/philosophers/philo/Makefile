NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include
SRCS = src/main.c src/init_philo.c src/philoing.c src/utils_1.c src/utils_2.c src/moni.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

%.o : %.c
	${CC} ${CFLAGS} ${INCLUDE} -c $^ -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
