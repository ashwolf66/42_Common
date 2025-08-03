#include "Socket.hpp"

Socket::~Socket()
{
	close(fd);
}

int	Socket::set_flag_fd(int serv_fd, int flags)
{
	if (fcntl(serv_fd, F_SETFL, flags) < 0)
	{
		close(serv_fd);
		std::cerr << "Failed to set socket to non-blocking mode" << std::endl;
		return 1;
	}
	return 0;
}

int	Socket::getFd()
{
	return fd;
}

int	Socket::getPort()
{
	return ntohs(addr.sin_port);
}

std::string Socket::getIp()
{
	return Ip;
}

bool Socket::setIp()
{
	Ip = inet_ntoa(addr.sin_addr);
	if (Ip.empty())
	{
		std::cerr << "Failed to get IP address." << std::endl;
		return true;
	}
	return false;
}

