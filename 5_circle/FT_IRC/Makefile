NAME		= ircserv
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98

SRCS		= main.cpp												\
			utils.cpp												\
			class/Socket/Socket.cpp									\
			class/Client/Client.cpp									\
			class/Client/ClientGetSet.cpp							\
			class/Client/channel.cpp								\
			class/Client/Client_create_error/Client_create_error.cpp\
			class/Server/Server.cpp									\
			class/Server/ServerGetSet.cpp							\
			class/ClientManager/ClientManager.cpp					\
			class/Channel/Channel.cpp								\
			class/Channel/mode.cpp									\
			class/Channel/ChannelFind.cpp							\
			class/ChannelManager/ChannelManager.cpp					\
			class/Server/check_event.cpp							\
			class/Server/handle_event.cpp	

			  
OBJS		= $(SRCS:.cpp=.o)


all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

cm:
	make fclean
	make all
	make clean

.PHONY: all clean fclean re cm

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

