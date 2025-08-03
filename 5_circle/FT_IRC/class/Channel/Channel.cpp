#include "Channel.hpp"

Channel::Channel(std::string name) : _Name(name), _Password(""), _Topic(""), _TopicWriter(""), _Limit(-1), _IFlag(false), _TFlag(false)
{
	_InitTimeToServer = std::time(NULL);
}

Channel::~Channel()
{
}

std::string &Channel::getName()
{
	return _Name;
}

void Channel::DisconnetionClient(Client *client, const std::string &msg)
{
	std::list<Client *> *where;
	std::list<Client *>::iterator it;
	std::ostringstream o_msg;

	o_msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" << client->getIp() << " QUIT :Quit: " << msg << "\r\n";

	if (FindClient(client, it, &where))
	{
		broadcast(client, o_msg);
		it = where->erase(it);
	}
}

void Channel::broadcast(Client *client, std::ostringstream &msg)
{
	for (std::list<Client *>::iterator it = _OpClients.begin(); it != _OpClients.end(); ++it)
	{
		if (*it == client)
			continue;
		(*it)->sendMessage(msg);
	}
	for (std::list<Client *>::iterator it = _ReClients.begin(); it != _ReClients.end(); ++it)
	{
		if (*it == client)
			continue;
		(*it)->sendMessage(msg);
	}
}

void Channel::writeJoinedClientNameList(Client *client, std::ostringstream &msg)
{
	msg << ":" << Server::getHostname() << " 353 " << client->getNickname() << " = " << _Name << " :";

	for (std::list<Client *>::iterator it = _OpClients.begin(); it != _OpClients.end(); ++it)
		msg << "@" << (*it)->getNickname() << " ";

	for (std::list<Client *>::iterator it = _ReClients.begin(); it != _ReClients.end(); ++it)
	{
		msg << (*it)->getNickname();
		if (it != --_ReClients.end())
			msg << " ";
	}

	msg << "\r\n"
		<< ":" << Server::getHostname() << " 366 " << client->getNickname() 
		<< " " << _Name << " :End of NAMES list.\r\n";
}

void Channel::join(Client *client, std::string &password)
{
	std::ostringstream msg;

	if (!_Password.empty() && _Password != password)
	{
		msg << ":" << Server::getHostname() << " 475 " << client->getUsername()
			<< " " << _Name << " :Cannot join Channel (+k)\r\n";
		client->sendMessage(msg);
		return;
	}

	if (_IFlag == true)
	{
		if (isInviteClient(client) == false)
		{
			msg << ":" << Server::getHostname() << " 473 " << client->getUsername() << " " << _Name << " :Cannot join Channel (+i)\r\n";
			client->sendMessage(msg);
			return;
		}
		_InviteList.erase(std::find(_InviteList.begin(), _InviteList.end(), client));
	}

	(_OpClients.size() == 0 ? _OpClients : _ReClients).push_back(client);
	client->addChannel(this);

	msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" << client->getHostname() << " JOIN :" << _Name << "\r\n";

	if (_Topic != "")
		msg << ":" << Server::getHostname() << " 332 " << client->getNickname() << " " << _Name << " " << _Topic << "\r\n" << ":" << Server::getHostname() << " 333 " << _TopicWriter << "!~" << client->getUsername() << "@" << client->getHostname() << " " << _InitTimeToTopic << "\r\n";

	writeJoinedClientNameList(client, msg);
	client->sendMessage(msg);
	
	msg.str("");
	msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" << client->getHostname() << " JOIN :" << _Name << "\r\n";
	broadcast(client, msg);
}

void Channel::privmsg(Client *client, std::string &msg)
{
	std::ostringstream o_msg;

	o_msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" 
		<< client->getHostname() << " PRIVMSG " << _Name << " " << msg << "\r\n";

	broadcast(client, o_msg);
}

void Channel::kick(Client *client, std::string nick, std::string reason)
{
	std::ostringstream msg;
	std::list<Client *> *where;
	std::list<Client *>::iterator it;

	if (FindOpClient(client, it) == false)
	{
		msg << ":" << Server::getHostname() << " 482 " << client->getNickname() << " "
			<< _Name << " :You must be a channel op or higher to kick a more privileged user.\r\n";
		client->sendMessage(msg);
		return;
	}

	if (FindClient(nick, it, &where) == false)
	{
		msg << ":" << Server::getHostname() << " 401 " << client->getNickname() << " "
			<< nick << " :No such nick\r\n";
		client->sendMessage(msg);
		return;
	}

	msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" << client->getHostname() 
		<< " KICK " << _Name << " " << nick << " " << (reason == "" ? ":no reason" : reason) << "\r\n";

	client->sendMessage(msg);
	(*it)->sendMessage(msg);
	(*it)->leave_channels(this);
	where->erase(it);
	broadcast(client, msg);
}

void Channel::invite(Client *client, std::string nick, ClientManager *clientManager)
{
	Client *client_tmp;
	std::ostringstream msg;
	std::list<Client *>::iterator it;

	if (FindOpClient(client, it) == false)
	{
		msg << ":" << Server::getHostname() << " 482 " << client->getNickname() << " "
			<< _Name << " :You must be a channel op or higher to send an invite.\r\n";
		client->sendMessage(msg);
		return;
	}

	if (FindClient(nick, it, NULL) == true)
	{
		msg << ":" << Server::getHostname() << " 443 " << client->getNickname() << " "
			<< nick << " " << _Name << " :is already on channel\r\n";
		client->sendMessage(msg);
		return;
	}

	client_tmp = clientManager->find_nick(nick);
	if (client_tmp == NULL)
	{
		msg << ":" << Server::getHostname() << " 401 " << client->getNickname() << " "
			<< nick << " :No such nick\r\n";
		client->sendMessage(msg);
		return;
	}

	if (isInviteClient(client_tmp) == false)
		_InviteList.push_back(client_tmp);
	msg << ":" << Server::getHostname() << " 341 " << client->getNickname() << " " << nick << " :" << _Name << "\r\n";
	client->sendMessage(msg);

	msg.str("");
	msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" << client->getHostname() << " INVITE " << nick << " :" << _Name << "\r\n";
	client_tmp->sendMessage(msg);
}

void Channel::topic(Client *client, std::string topic)
{
	std::ostringstream msg;

	if (_TFlag == false && FindOpClient(client) == false)
	{
		msg << ":" << Server::getHostname() << " 482 " << client->getNickname() << " "
			<< _Name << " :You must be a channel op or higher to change the topic.\r\n";
		client->sendMessage(msg);
		return;
	}

	msg << ":" << client->getNickname()
		<< "!" << client->getUsername()
		<< "@" << client->getHostname() << " TOPIC " << _Name << " " << topic << "\r\n";

	_Topic = topic;
	_TopicWriter = client->getNickname();
	_InitTimeToTopic = std::time(NULL);
	client->sendMessage(msg);
	broadcast(client, msg);
}

bool Channel::setFlag(Client *client, std::string &flag, char &toggle_sign, std::vector<std::string>::iterator &param_it, std::vector<std::string> &params)
{
	std::ostringstream msg;

	if (isInvalidModeFlag(flag))
	{
		msg << ":" << Server::getHostname() << " 501 " << client->getNickname() << " : " << flag << " is not a recognised channel mode\r\n";
		client->sendMessage(msg);
		return false;
	}

	if (flag.size() == 1)
		flag = toggle_sign + flag;
	else
		toggle_sign = flag[0];
	
	if (isUsedParamMode(flag) && param_it != params.end())
		param_it++;
	return true;
}

bool	Channel::selectMode(Client *client, std::string &flag, const std::string &param)
{
	if (flag[1] == 'i')
		return I_Option(client, flag);
	if (flag[1] == 't')
		return T_Option(client, flag);
	if (flag[1] == 'k')
		return K_Option(client, flag, param);
	if (flag[1] == 'o')
		return O_Option(client, flag, param);
	return L_Option(client, flag, param);
}

void Channel::mode(Client *client, std::vector<std::string> flags, std::vector<std::string> params)
{
	std::ostringstream msg;
	std::string apply_mode;
	std::pair<std::string, std::string> param_pair;

	if (flags.empty())
	{
		msg << ":" << Server::getHostname() << " 324 " << client->getNickname() << " " << _Name << " :+\r\n";
		if (_IFlag) msg << "i";
		if (_TFlag) msg << "t";
		if (!_Password.empty()) msg << "k " << _Password;
		if (_Limit >= 0) msg << "l " << _Limit;
		msg << ":" << Server::getHostname() << " 329 " << client->getNickname() << " " << _Name << " :" << _InitTimeToServer << "\r\n";
		client->sendMessage(msg);
		return;
	}
	
	char toggle_sign = '+';
	std::vector<std::string>::iterator param_it = params.begin();
	for (std::size_t i = 0; i < flags.size(); ++i)
	{
		std::string flag = flags[i];
		std::string param = (param_it != params.end()) ? *param_it : "";

		if (setFlag(client, flag, toggle_sign, param_it, params) == false || \
			selectMode(client, flag, param) == false)
			continue;
		if (isUsedParamMode(flag))
		{
			if (param_pair.second.empty() == false) param_pair.first += " " + param_pair.second;
			param_pair.second = param;
		}
		apply_mode += flags[i];
	}

	if (apply_mode.empty())
		return;

	msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" << client->getHostname() << " MODE " << _Name;
	if (param_pair.second.empty())
		msg << " :" << apply_mode << "\r\n";
	else
		msg << " " << apply_mode << param_pair.first << " :" << param_pair.second << "\r\n";

	client->sendMessage(msg);
	broadcast(client, msg);
}

void Channel::part(Client *client, std::string reason)
{
	std::ostringstream msg;
	std::list<Client *> *where;
	std::list<Client *>::iterator it;

	if (FindClient(client, it, &where) == false)
	{
		msg << ":" << Server::getHostname() << " 442 " << client->getNickname() << " "
			<< _Name << " :You're not on that channel\r\n";
		client->sendMessage(msg);
		return;
	}

	msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" << client->getHostname() << " PART " << _Name << " :" << reason << "\r\n";
	client->sendMessage(msg);
	broadcast(client, msg);

	where->erase(it);
	client->leave_channels(this);
}

void Channel::who(Client *client, std::string &str)
{
	std::ostringstream msg;

	if (str.empty() == false)
	{
		msg << ":" << Server::getHostname() << " 315 " << client->getNickname() << " " << _Name << " :End of /WHO list\r\n";
		client->sendMessage(msg);
		return;
	}

	msg << ":" << Server::getHostname() << " 352 " << client->getNickname() << " " << _Name << " :";
	for (std::list<Client *>::iterator it = _OpClients.begin(); it != _OpClients.end(); ++it)
		msg << (*it)->getNickname() << " ";
	for (std::list<Client *>::iterator it = _ReClients.begin(); it != _ReClients.end(); ++it)
		msg << (*it)->getNickname() << " ";
	msg << "\r\n";
	msg << ":" << Server::getHostname() << " 315 " << client->getNickname() << " " << _Name << " :End of /WHO list\r\n";
	client->sendMessage(msg);
}
