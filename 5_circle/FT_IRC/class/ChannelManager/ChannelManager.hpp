#pragma once
#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

#include "../Channel/Channel.hpp"
#include "../Client/Client.hpp"
#include "../ClientManager/ClientManager.hpp"

class ChannelManager
{
private:
	std::vector<Channel *> _Channels;

public:
	ChannelManager(/* args */);
	~ChannelManager();

	void	add(std::string &name);
	void	del(std::string &name);
	Channel	*find(std::string &name);

	void 	send_not_joined(Client *client, std::string &channel);

	void 	join(std::vector<std::string> &channels, Client *client, std::vector<std::string> &passwords);
	void 	privmsg(std::string &channels, Client *client, std::string &msg);
	void 	kick(std::string &channel, Client *client, std::string &nick, std::string &reason);
	void 	invite(std::string &channel, Client *client, std::string &nick, ClientManager *clientManager);
	void 	topic(std::string &channel, Client *client, std::string &topic);
	void 	mode(std::string &channel, Client *client, std::vector<std::string> &modes, std::vector<std::string> &str);
	void	part(std::string &channel, Client *client, std::string &reason);
};

#endif