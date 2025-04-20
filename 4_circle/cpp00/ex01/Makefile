SRCS	=	./MyAwesomePhoneBook.cpp \
			./Contact.cpp \
			./PhoneBook.cpp
CC		= g++
NAME	= PhoneBook
CFLAGS	= -Wall -Wextra -Werror -std=c++98
OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.c
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re