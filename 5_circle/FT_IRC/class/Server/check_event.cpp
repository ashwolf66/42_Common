#include "Server.hpp"

bool Server::check_client_connection(epoll_event &event)
{
	return static_cast<Client *>(event.data.ptr)->getFd() == this->fd;
}

bool Server::check_client_disconnection(epoll_event &event)
{
	return static_cast<Client *>(event.data.ptr)->getFd() != this->fd && (event.events & (EPOLLRDHUP | EPOLLERR));
}

bool Server::check_client_readable(epoll_event &event)
{
	return static_cast<Client *>(event.data.ptr)->getFd() != this->fd && (event.events & (EPOLLIN));
}

int Server::handle_cmd(t_str_pair &cmd_pair, Client *client)
{
	if (cmd_pair.first == "PASS")
		handle_pass(cmd_pair.second, client);
	else if (cmd_pair.first == "NICK")
		handle_nick(cmd_pair.second, client);
	else if (cmd_pair.first == "USER")
		handle_user(cmd_pair.second, client);
	else if (cmd_pair.first == "JOIN")
		handle_join(cmd_pair.second, client);
	else if (cmd_pair.first == "PRIVMSG")
		handle_privmsg(cmd_pair.second, client);
	else if (cmd_pair.first == "KICK")
		handle_kick(cmd_pair.second, client);
 	else if (cmd_pair.first == "INVITE")
		handle_invite(cmd_pair.second, client, cm);
	else if (cmd_pair.first == "TOPIC")
		handle_topic(cmd_pair.second, client);
	else if (cmd_pair.first == "MODE")
		handle_mode(cmd_pair.second, client);
	else if (cmd_pair.first == "PING")
		handle_ping(cmd_pair.second, client);
	else if (cmd_pair.first == "QUIT")
		handle_quit(cmd_pair.second, client);
	else if (cmd_pair.first == "PART")
		handle_part(cmd_pair.second, client);
	else if (cmd_pair.first == "WHOIS")
		return 0;
	else if (cmd_pair.first == "WHO")
		return 0;
	else if (cmd_pair.first == "CAP")
		return 0;
	else 
	{
		std::ostringstream msg;
		msg << ":" << Server::getHostname() << " 421 " << client->getNickname() << " " << cmd_pair.first << " :Unknown command\r\n";
		client->sendMessage(msg);
		return -1;
	}
	return 0;
}

std::vector<std::string> Server::split_mode(std::string &modes)
{
	std::vector<std::string> result;

	if (modes.empty())
		return result;

	for (size_t i = 0; i < modes.size() && modes[i]; ++i)
	{
		std::string toggle_sign = "";
		while (i < modes.size() && (modes[i] == '+' || modes[i] == '-'))
			toggle_sign = modes[i++];
		result.push_back(toggle_sign + modes[i]);
	}

	return result;
}




