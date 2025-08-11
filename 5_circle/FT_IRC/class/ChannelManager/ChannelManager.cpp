#include "ChannelManager.hpp"

ChannelManager::ChannelManager(/* args */)
{
}

ChannelManager::~ChannelManager()
{
	for (std::vector<Channel *>::iterator it = _Channels.begin(); it != _Channels.end(); ++it)
		delete *it;
	_Channels.clear();
}

void ChannelManager::add(std::string &name)
{
	if (find(name) == NULL)
		_Channels.push_back(new Channel(name));
}

void ChannelManager::del(std::string &name)
{
	for (std::vector<Channel *>::iterator it = _Channels.begin(); it != _Channels.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			delete *it;
			_Channels.erase(it);
			break;
		}
	}
}

Channel *ChannelManager::find(std::string &name)
{
	for (std::vector<Channel *>::iterator it = _Channels.begin(); it != _Channels.end(); it++)
	{
		if ((*it)->getName() == name)
			return *it;
	}
	return NULL;
}

void ChannelManager::send_not_joined(Client *client, std::string &channel)
{
	std::ostringstream msg;
	msg << ":" << Server::getHostname() << " 442 " << client->getNickname() << " " << channel << " :You're not on that channel\r\n";
	client->sendMessage(msg);
}

void ChannelManager::join(std::vector<std::string> &channels, Client *client, std::vector<std::string> &passwords)
{
	size_t i_pass = 0;
	std::ostringstream msg;
	for (size_t i = 0; i < channels.size(); ++i)
	{
		if (channels[i].empty() == false && channels[i][0] != '#')
		{
			msg << ":" << Server::getHostname() << " 403 " << client->getNickname() << " " << channels[i] 
				<< " :Invalid channel name\r\n";
			continue;
		}
		Channel* channel = find(channels[i]);
		if (!channel)
		{
			channel = new Channel(channels[i]);
			_Channels.push_back(channel);
		}
		channel->join(client, passwords[i_pass++], msg);
	}
	client->sendMessage(msg);
}

void ChannelManager::privmsg(std::string &channel, Client *client, std::string &msg)
{
	Channel *channel_tmp = find(channel);
	if (channel_tmp == NULL)
	{
		std::ostringstream msg;
		msg << ":" << Server::getHostname() << " 403 " << client->getNickname() << " " << channel 
			<< " :No such channel\r\n";
		client->sendMessage(msg);
		return;
	}

	channel_tmp->privmsg(client, msg);
}

void ChannelManager::kick(std::string &channel, Client *client, std::string &nick, std::string &reason)
{
	Channel *channel_tmp = find(channel);
	if (channel_tmp == NULL)
	{
		std::ostringstream msg;
		msg << ":" << Server::getHostname() << " 403 " << client->getNickname() << " " << channel 
			<< " :No such channel\r\n";
		client->sendMessage(msg);
		return;
	}
	if (client->isInChannel(channel) == false)
	{
		send_not_joined(client, channel);
		return;
	}
	channel_tmp->kick(client, nick, reason);
}

void ChannelManager::invite(std::string &channel, Client *client, std::string &nick, ClientManager *clientManager)
{
	Channel *channel_tmp = find(channel);
	if (channel_tmp == NULL)
	{
		std::ostringstream msg;
		msg << ":" << Server::getHostname() << " 403 " << client->getNickname() << " " << channel 
			<< " :No such channel\r\n";
		client->sendMessage(msg);
		return;
	}
	if (client->isInChannel(channel) == false)
	{
		send_not_joined(client, channel);
		return;
	}
	channel_tmp->invite(client, nick, clientManager);
}

void ChannelManager::topic(std::string &channel, Client *client, std::string &topic)
{
	Channel *channel_tmp = find(channel);
	if (channel_tmp == NULL)
	{
		std::ostringstream msg;
		msg << ":" << Server::getHostname() << " 403 " << client->getNickname() << " " << channel 
			<< " :No such channel\r\n";
		client->sendMessage(msg);
		return;
	}
	if (client->isInChannel(channel) == false)
	{
		send_not_joined(client, channel);
		return;
	}
	channel_tmp->topic(client, topic);
}

void ChannelManager::mode(std::string &channel, Client *client, std::vector<std::string> &modes, std::vector<std::string> &str)
{
	Channel *channel_tmp = find(channel);
	if (channel_tmp == NULL)
	{
		std::ostringstream msg;
		msg << ":" << Server::getHostname() << " 403 " << client->getNickname() << " " << channel 
			<< " :No such channel\r\n";
		client->sendMessage(msg);
		return;
	}
	channel_tmp->mode(client, modes, str);
}

void ChannelManager::part(std::string &channel, Client *client, std::string &reason)
{
	Channel *channel_tmp = find(channel);
	if (channel_tmp == NULL)
	{
		std::ostringstream msg;
		msg << ":" << Server::getHostname() << " 403 " << client->getNickname() << " " << channel << " :No such channel\r\n";
		client->sendMessage(msg);
		return;
	}
	if (client->isInChannel(channel) == false)
	{
		send_not_joined(client, channel);
		return;
	}
	channel_tmp->part(client, reason);
	
}
