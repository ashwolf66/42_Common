#include "Server.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../ChannelManager/ChannelManager.hpp"

void Server::send_registered(Client *client)
{
	std::ostringstream msg;

	if (client->getIsRegistered() == true)
		return;
	if (client->getNickname() == "*" || client->getUsername() == "*")
		return;

	if (client->getIsPasswordValid() == false)
	{
		msg << "ERROR : Closing Link: (" << client->getUsername() << "@" << client->getHostname() << ") [Bad Password]\r\n";
		client->sendMessage(msg);
		cm->del(client);
		return;
	}
	
	client->setIsRegistered(true);
	msg << ":" << Server::getHostname() << " 001 " << client->getNickname() << " :Welcome to the Internet Relay Network " << client->getNickname() << "!" << client->getUsername() << "@" << client->getHostname() << "\r\n";
	client->sendMessage(msg);
}

void Server::send_not_registered(Client *client)
{
	std::ostringstream msg;
	msg << ":" << Server::getHostname() << " 451 " << client->getNickname() << " :You have not registered\r\n";
	client->sendMessage(msg);
}



void	Server::handle_pass(std::string &password, Client *client)
{
	if (this->password == password)
		client->setIsPasswordValid(true);
}

bool is_valid_name(const std::string &nickname)
{
	std::ostringstream msg;
	
	if (std::isalpha(nickname[0]) == false && nickname[0] != '_')
		return false;

	for (size_t i = 0; i < nickname.length(); ++i)
	{
		if (!std::isalnum(nickname[i]) && nickname[i] != '-' && nickname[i] != '_')
		{
			return false;
		}
	}

	return true;
}

void	Server::handle_nick(std::string &nickname, Client *client)
{
	std::ostringstream msg;

	if (nickname.empty())
	{
		msg << ":" << Server::getHostname() << " 461 " << client->getNickname() << " NICK :Not enough parameters.\r\n";
		client->sendMessage(msg);
		return;
	}

	nickname = get_front(nickname, ' ');

	if (is_valid_name(nickname) == false)
	{
		msg << ":" << Server::getHostname() << " 432 " << client->getNickname() << " " << nickname << " :Erroneous nickname\r\n";
		client->sendMessage(msg);
		return;
	}

	if (client->getNickname() == nickname)
		return;

	if (cm->find_nick(nickname) != NULL)
	{
		msg << ":" << Server::getHostname() << " 433 " << client->getNickname() << " " << nickname << " :Nickname is already in use\r\n";
		client->sendMessage(msg);
		return;
	}

	if (client->getNickname() != "*")
	{
		msg << ":" << client->getNickname() << "!~" << client->getUsername() << "@" << client->getHostname() << " NICK :" << nickname << "\r\n";
		client->sendMessage(msg);
		client->setNickname(nickname);
		return;
	}

	client->setNickname(nickname);
	send_registered(client);
}

void	Server::handle_user(std::string &str, Client *client)
{
	std::ostringstream msg;
	std::vector<std::string> tokens = split(str, ' ');

	if (str.empty() || tokens.size() < 4)
	{
		msg << ":" << Server::getHostname() << " 461 " << client->getNickname() << " USER :Not enough parameters\r\n";
		client->sendMessage(msg);
		return;
	}
	if (is_valid_name(tokens[0]) == false)
	{
		msg << ":" << Server::getHostname() << " 468 " << client->getNickname() << " USER :Your username is not valid\r\n";
		client->sendMessage(msg);
		return;
	}
	client->setUsername(tokens[0]);
	client->setServername(tokens[2]);
	std::string realname = tokens[3].substr(1);
	client->setRealname(realname);

	send_registered(client);
}

void	Server::handle_join(std::string &str, Client *client)
{
	if (client->getIsRegistered() == false)
		return send_not_registered(client);
	if (str.empty())
	{
		std::ostringstream msg;
		msg << ":" << Server::getHostname() << " 461 " << client->getNickname() << " JOIN :Not enough parameters\r\n";		
		client->sendMessage(msg);
		return;
	}
	
	t_str_pair seq = split_prev(str);
	std::vector<std::string> channels = split(seq.first, ',');
	std::vector<std::string> passwords = split(seq.second, ',');

	size_t fill_size = channels.size() - passwords.size();
	for (size_t i = 0; i < fill_size; ++i)
		passwords.push_back("");
		
	ch_manager->join(channels, client, passwords);
}

void	Server::handle_privmsg(std::string &str, Client *client)
{
	std::ostringstream msg;

	if (client->getIsRegistered() == false)
		return send_not_registered(client);
	if (str.empty())
	{
		msg << ":" << Server::getHostname() << " 461 " << client->getNickname() << " PRIVMSG :Not enough parameters\r\n";
		client->sendMessage(msg);
		return;
	}
	
	t_str_pair res = split_prev(str);
	if (res.second.empty())
	{
		msg << ":" << Server::getHostname() << " 411 " << client->getNickname() << " :No recipient given (PRIVMSG)\r\n";
		client->sendMessage(msg);
		return;
	}

	std::vector<std::string> receiver = split(res.first, ',');
	for (size_t i = 0; i < receiver.size(); ++i)
	{
		if (receiver[i][0] == '#')
			ch_manager->privmsg(receiver[i], client, res.second);
		else
			cm->privmsg(receiver[i], client, res.second);
	}
}

void	Server::handle_kick(std::string &str, Client *client)
{
	std::string ch_name;
	std::string target;
	std::string reason;

	if (client->getIsRegistered() == false)
		return send_not_registered(client);
	
	t_str_pair res = split_prev(str);
	ch_name = res.first;
	res = split_prev(res.second);
	target = res.first;
	reason = res.second;
	ch_manager->kick(ch_name, client, target, reason);
}

void	Server::handle_invite(std::string &str, Client *client, ClientManager *cm)
{
	if (client->getIsRegistered() == false)
		return send_not_registered(client);

	t_str_pair res = split_prev(str);
	std::string nick = res.first;
	std::string channel = res.second;
	ch_manager->invite(channel, client, nick, cm);
}

void	Server::handle_topic(std::string &str, Client *client)
{
	if (client->getIsRegistered() == false)
		return send_not_registered(client);

	t_str_pair res = split_prev(str);
	std::string channel = res.first;
	std::string topic = res.second;
	ch_manager->topic(channel, client, topic);
}

void	Server::handle_mode(std::string &str, Client *client)
{
	if (client->getIsRegistered() == false)
		return send_not_registered(client);

	std::string target;
	std::vector<std::string> modes;
	std::vector<std::string> values;

	t_str_pair res = split_prev(str);
	target = res.first;
	res = split_prev(res.second);
	modes = split_mode(res.first);
	values = split(res.second, ' ');

	if (target[0] == '#')
		ch_manager->mode(target, client, modes, values);
	else
		cm->mode(target, client, modes);
}

void Server::handle_ping(std::string &str, Client *client)
{
	if (client->getIsRegistered() == false)
		return send_not_registered(client);

	std::ostringstream msg;
	if (str.empty())
	{
		msg << ":" << Server::getHostname() << " 409 " << client->getNickname() << " :No origin specified\r\n";
		client->sendMessage(msg);
		return;
	}
	msg << ":" << Server::getHostname() << " PONG " << str << " :" << Server::getHostname() << "\r\n";
	client->sendMessage(msg);
}

void Server::handle_quit(std::string &str, Client *client)
{
	if (client->getIsRegistered() == false)
		return send_not_registered(client);
	str = str.substr(1);
	client->quit(str);
}

void Server::handle_part(std::string &str, Client *client)
{
	if (client->getIsRegistered() == false)
		return send_not_registered(client);

	t_str_pair res = split_prev(str);
	std::string channel = res.first;
	std::string reason = res.second;

	ch_manager->part(channel, client, reason);
}
