# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jacha <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 19:32:48 by jacha             #+#    #+#              #
#    Updated: 2024/06/17 16:01:19 by jacha            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= pipex.c pipex_utils.c
OBJS	= ${SRCS:.c=.o}
NAME	= pipex
MAIN	= pipex.c
INCLUDE	= .
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rc

%.o : %.c
	${CC} ${CFLAGS} -c $^ -I . -o $@

all		: ${NAME}

${NAME}	: ${OBJS}
	$(MAKE) bonus -C libft
	${CC} ${CFLAGS} ${OBJS} libft/libft.a -o ${NAME}

clean	:
	rm -f ${OBJS}
	$(MAKE) clean -C libft

fclean	:
	$(MAKE) clean
	$(RM) libft/*.a
	rm -f ${NAME}

re	:
	$(MAKE) fclean
	$(MAKE) all	

.phony	: all re clean fclean
