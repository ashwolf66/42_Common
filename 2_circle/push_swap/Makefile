# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jacha <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 15:27:13 by jacha             #+#    #+#              #
#    Updated: 2024/06/17 20:50:25 by jacha            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= push_swap.c r_op.c s_op.c last_point.c p_op.c rr_op.c sort.c  \
sort_utils_1.c free.c
OBJS	= ${SRCS:.c=.o}
NAME	= push_swap
MAIN	= push_swap.c
INCLUDE	= .
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rc

%.o : %.c
	${CC} ${CFLAGS} -c $^ -I . -o $@

all		: ${NAME}

${NAME} : ${OBJS}
	$(MAKE) bonus -C libft
	${CC} ${CFLAGS} ${OBJS} libft/libft.a -o ${NAME}

clean	:
	rm -f ${OBJS}
	$(MAKE) clean -C libft

fclean	:
	$(MAKE) clean
	$(RM) libft/*.a
	rm -f ${NAME}

re		:
	$(MAKE) fclean
	$(MAKE) all

.phony	: all re clean fclean
