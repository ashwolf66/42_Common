SRCS = ft_printf.c ft_putnbr_base.c hex_print.c int_print.c char_print.c
OBJS = ${SRCS:.c=.o}
NAME = libftprintf.a
INCLUDE = .
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc

.phony : all re clean fclean bonus 

all : ${NAME}

${NAME} : ${OBJS}
	$(MAKE) bonus -C libft
	cp libft/libft.a $(NAME)
	${AR} ${NAME} ${OBJS}

%.o : %.c
	${CC} ${CFLAGS} -c $^ -I . -o $@

clean :
	rm -f ${OBJS}
	$(RM) libft/*.o

fclean :
	make clean
	$(RM) libft/*.a
	rm -f ${NAME}

re : 
	make fclean
	make all
