#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "../../ft_irc.hpp"

class Socket
{
protected:
	int			fd;
	sockaddr_in	addr;
	std::string	Ip;
public:
	Socket(){}
	virtual ~Socket();

	int				set_flag_fd(int serv_fd, int flags);
	int				getFd();
	int				getPort();

	std::string 	getIp();
	virtual bool	setIp();
};

#endif