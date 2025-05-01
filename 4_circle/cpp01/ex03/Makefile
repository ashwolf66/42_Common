# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 15:50:12 by jacha             #+#    #+#              #
#    Updated: 2025/05/01 12:42:11 by jacha            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.cpp \
			Weapon.cpp \
			HumanA.cpp \
			HumanB.cpp
CC		= c++
NAME	= UnnecessaryViolence
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
