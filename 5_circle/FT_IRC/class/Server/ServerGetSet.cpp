#include "Server.hpp"

int Server::get_epfd()
{
	return epfd;
}

void Server::set_epfd(int epfd)
{
	Server::epfd = epfd;
}

std::string Server::getHostname()
{
	return Server::hostname;
}

time_t Server::getTime()
{
	Server::time = std::time(NULL);
	if (Server::time == -1)
		throw std::runtime_error("Failed to get current time");
	return Server::time;
}

bool Server::get_exit_flag()
{
	return exit_flag;
}

void Server::set_exit_flag(bool flag)
{
	exit_flag = flag;
}
