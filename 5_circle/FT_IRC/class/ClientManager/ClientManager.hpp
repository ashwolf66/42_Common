#pragma once
#ifndef CLIENTMANAGER_HPP
# define CLIENTMANAGER_HPP

#include "../Client/Client.hpp"

class ClientManager
{
private:
	std::vector<Client *>		clients;
public:
	ClientManager(/* args */);
	~ClientManager();

	bool	add(int serv_fd);
	void	del(epoll_event &event);
	void	del(Client *client);

	Client *find_fd(int fd);
	Client *find_nick(std::string &nick);

	bool	isInvalidModeFlag(const std::string &flag);
	bool	selectMode(Client *client, std::string &flag, char &toggle_sign);
	void	mode(std::string target, Client *client, std::vector<std::string> &modes);
};

#endif
