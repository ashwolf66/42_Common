# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 15:27:28 by jacha             #+#    #+#              #
#    Updated: 2025/05/24 16:31:51 by jacha            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.cpp \
			RPN.cpp
CC		= c++
NAME	= RPN
CFLAGS	= -Wall -Wextra -Werror -std=c++98
OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.cpp
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
