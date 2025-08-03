#include "ClientManager.hpp"
#include "../Server/Server.hpp"
#include "../Client/Client_create_error/Client_create_error.hpp"

ClientManager::ClientManager(/* args */)
{

}

ClientManager::~ClientManager()
{
	std::ostringstream msg;

	for (std::list<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		msg << "ERROR :Closing link: " << (*it)->getUsername() << "@" << (*it)->getIp() << ":" << (*it)->getPort() << " [Server shutting down]\r\n";
		(*it)->sendMessage(msg);
		msg.str("");
		delete *it;
	}
	clients.clear();
}

bool ClientManager::add(int serv_fd)
{
	Client *new_client;

	try { new_client = new Client(serv_fd, Server::get_epfd()); }
	catch (const ClientCreateError &e)
	{
		std::cerr << "Error creating client: " << e.what() << std::endl;
		return false;
	}
	catch (const std::exception &e)
	{
		throw;
	}
	clients.push_back(new_client);
	new_client->lookingHostname();
	return true;
}

void ClientManager::del(epoll_event &event)
{
	Client *client = static_cast<Client *>(event.data.ptr);

	clients.erase(std::find(clients.begin(), clients.end(), client));
	delete client;
}

void ClientManager::del(Client *client)
{
	clients.erase(std::find(clients.begin(), clients.end(), client));
	delete client;
}

Client* ClientManager::find_fd(int fd)
{
	for (std::list<Client *>::iterator i = clients.begin(); i != clients.end(); ++i)
	{
		if ((*i)->getFd() == fd)
		{
			std::cout << "Client found with fd: " << fd << std::endl;
			return *i;
		}
	}
	std::cout << "No client found with fd: " << fd << std::endl;
	return NULL;
}

Client* ClientManager::find_nick(std::string &nick)
{
	for (std::list<Client *>::iterator i = clients.begin(); i != clients.end(); ++i)
	{
		if ((*i)->getNickname() == nick)
		{
			return *i;
		}
	}
	return NULL;
}

bool ClientManager::isInvalidModeFlag(const std::string &flag)
{
	return (flag != "+i" && flag != "-i");
}

bool ClientManager::selectMode(Client *client, std::string &flag, char &toggle_sign)
{
	if (isInvalidModeFlag(flag))
	{
		std::ostringstream msg;
		msg << ":" << Server::getHostname() << " 501 " << client->getNickname() << " : " << flag << " is not a recognised user mode\r\n";
		client->sendMessage(msg);
		return false;
	}

	if (flag.size() == 1)
		flag = toggle_sign + flag;
	else
		toggle_sign = flag[0];

	if (flag[1] == 'i')
	{
		if (flag == "+i" && client->getIsInvisible() == false)
		{
			client->setIsInvisible(true);
			return true;
		}
		else if (flag == "-i" && client->getIsInvisible() == true)
		{
			client->setIsInvisible(false);
			return true;
		}
	}
	return false;
}

void ClientManager::mode(std::string target_name, Client *client, std::vector<std::string> &flags)
{
	std::ostringstream msg;
	std::string apply_mode;

	Client *target = find_nick(target_name);
	if (target == NULL)
	{
		msg << ":" << Server::getHostname() << " 401 " << client->getNickname() << " " << target_name << " :No such nick/channel\r\n";
		client->sendMessage(msg);
		return;
	}
	if (target != client)
	{
		msg << ":" << Server::getHostname() << " 502 " << client->getNickname() << " :Cannot change mode for other users\r\n";
		client->sendMessage(msg);
		return;
	}

	if (flags.empty())
	{
		msg << ":" << Server::getHostname() << " 221 " << target->getNickname() << " :"
			<< (target->getIsInvisible() ? "+i" : "")
			<<"\r\n";
		client->sendMessage(msg);
		return;
	}

	char toggle_sign = '+';
	for (std::size_t i = 0; i < flags.size(); ++i)
	{
		std::string flag = flags[i];

		if (selectMode(client, flag, toggle_sign) == false)
			continue;
		apply_mode += flags[i];
	}

	if (apply_mode.empty())
		return;

	msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" << client->getHostname() << " MODE " << target->getNickname() << " :" << apply_mode << "\r\n";
	client->sendMessage(msg);
	return;
}