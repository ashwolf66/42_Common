#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include <sstream>
# include <map>
# include <set>
# include <algorithm>

# include <cstdlib>
# include <cstring>
# include <cctype>
# include <cerrno>
# include <cstdio>
# include <csignal>
# include <ctime>

# include <unistd.h>
# include <fcntl.h>
# include <netdb.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <sys/epoll.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define F_PASS		0
# define F_NICK		1
# define F_USER		2
# define F_JOIN		3
# define F_PRIVMSG	4
# define F_KICK		5
# define F_INVITE	6
# define F_TOPIC	7
# define F_MODE		8

# define BUFFER_SIZE 100
# define MAX_CLIENTS 100
# define MAX_EVENTS 10

typedef	std::pair<std::string, std::string> t_str_pair;

#endif