#include "Channel.hpp"

bool Channel::FindOpClient(Client *client)
{
	std::vector<Client *>::iterator it;
	for (it = _OpClients.begin(); it != _OpClients.end(); ++it)
	{
		if (*it == client)
			return true;
	}
	return false;
}

bool Channel::FindOpClient(Client *client, std::vector<Client *>::iterator &it)
{
	for (it = _OpClients.begin(); it != _OpClients.end(); ++it)
	{
		if (*it == client)
			return true;
	}
	return false;
}

bool Channel::FindOpClient(const std::string &nick, std::vector<Client *>::iterator &it)
{
	for (it = _OpClients.begin(); it != _OpClients.end(); ++it)
	{
		if ((*it)->getNickname() == nick)
			return true;
	}
	return false;
}

bool Channel::FindReClient(Client *client, std::vector<Client *>::iterator &it)
{
	for (it = _ReClients.begin(); it != _ReClients.end(); ++it)
	{
		if (*it == client)
			return true;
	}
	return false;
}

bool Channel::FindReClient(const std::string &nick, std::vector<Client *>::iterator &it)
{
	for (it = _ReClients.begin(); it != _ReClients.end(); ++it)
	{
		if ((*it)->getNickname() == nick)
			return true;
	}
	return false;
}

bool Channel::FindClient(Client *client, std::vector<Client *>::iterator &it, std::vector<Client *> **where)
{
	if (FindOpClient(client, it))
	{
		if (where != NULL)
			*where = &_OpClients;
		return true;
	}
	if (FindReClient(client, it))
	{
		if (where != NULL)
			*where = &_ReClients;
		return true;
	}
	return false;
}

bool Channel::FindClient(const std::string &nick, std::vector<Client *>::iterator &it, std::vector<Client *> **where)
{
	if (FindOpClient(nick, it))
	{
		if (where != NULL)
			*where = &_OpClients;
		return true;
	}
	if (FindReClient(nick, it))
	{
		if (where != NULL)
			*where = &_ReClients;
		return true;
	}
	return false;
}

bool Channel::isInviteClient(Client *client)
{
	for (std::vector<Client *>::iterator it = _InviteList.begin(); it != _InviteList.end(); ++it)
	{
		if (*it == client)
			return true;
	}
	return false;
}
