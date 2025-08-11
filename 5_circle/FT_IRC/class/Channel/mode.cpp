#include "Channel.hpp"

bool Channel::isInvalidModeFlag(std::string &flag)
{
	char mode_char;

	if (flag.size() == 2)
		mode_char = flag[1];
	else
		mode_char = flag[0];

	return mode_char != 'i' && mode_char != 't' && mode_char != 'k' && mode_char != 'o' && mode_char != 'l';
}

bool Channel::isUsedParamMode(const std::string &flag)
{
	return flag[1] == 'k' || flag[1] == 'o' || flag == "+l";
}

bool Channel::I_Option(Client *client, std::string flag, std::ostringstream &msg)
{
	
	if (FindOpClient(client) == false)
	{
		std::string what = (flag == "+i") ? "set" : "unset";
		msg << ":" << Server::getHostname() << " 482 " << client->getNickname() << " "
			<< _Name << " :You must be a channel op or higher to " << what << " channel mode i (inviteonly).\r\n";
		return false;
	}

	if (flag == "+i")
		_IFlag = true;
	else if (flag == "-i")
		_IFlag = false;
	return true;
}

bool Channel::T_Option(Client *client, std::string flag, std::ostringstream &msg)
{
	if (FindOpClient(client) == false)
	{
		std::string what = (flag == "+t") ? "set" : "unset";
		msg << ":" << Server::getHostname() << " 482 " << client->getNickname() << " "
			<< _Name << " :You must be a channel op or higher to " << what << " channel mode t (topiclock).\r\n";
		return false;
	}

	if (flag == "+t")
		_TFlag = false;
	else if (flag == "-t")
		_TFlag = true;
	return true;
}

bool Channel::K_Option(Client *client, std::string flag, std::string str, std::ostringstream &msg)
{
	if (str.empty())
	{
		msg << ":" << Server::getHostname() << " 696 " << client->getNickname() << " "
			<< _Name << " k * :You must specify a parameter for the key mod. Syntax: <key>.\r\n";
		return false;
	}
	if (FindOpClient(client) == false)
	{
		std::string what = (flag == "+k") ? "set" : "unset";
		msg << ":" << Server::getHostname() << " 482 " << client->getNickname() << " "
			<< _Name << " :You must be a channel op or higher to " << what << " channel mode k (key).\r\n";
		return false;
	}
	if (flag == "-k" && _Password != str)
	{
		msg << ":" << Server::getHostname() << " 487 " << client->getNickname() << " "
			<< _Name << " :Cannot key already set\r\n";
		return false;
	}

	if (flag == "+k")
		_Password = str;
	else if (flag == "-k")
		_Password = "";
	return true;
}

bool Channel::O_Option(Client *client, std::string flag, std::string str, std::ostringstream &msg)
{
	std::list<Client *>::iterator it;

	if (FindOpClient(client) == false)
	{
		std::string what = (flag == "+o") ? "set" : "unset";
		msg << ":" << Server::getHostname() << " 482 " << client->getNickname() << " "
			<< _Name << " :You must be a channel op or higher to " << what << " channel mode o (op).\r\n";
		return false;
	}
	if (str.empty())
	{
		msg << ":" << Server::getHostname() << " 696 " << client->getNickname() << " "
			<< _Name << " o * :You must specify a parameter for the op mod. Syntax: <nick>.\r\n";
		return false;
	}
	if (FindClient(str, it, NULL) == false)
	{
		msg << ":" << Server::getHostname() << " 401 " << client->getNickname() << " " << str << " :No such nick\r\n";
		return false;
	}

	(flag == "+o") ? _OpClients.push_back(*it)	: _ReClients.push_back(*it);
	(flag == "+o") ? _ReClients.erase(it)		: _OpClients.erase(it);
	return true;
}

bool Channel::L_Option(Client *client, std::string flag, std::string str, std::ostringstream &msg)
{
	if (FindOpClient(client) == false)
	{
		std::string what = (flag == "+l") ? "set" : "unset";
		msg << ":" << Server::getHostname() << " 482 " << client->getNickname() << " " << _Name << " :You must be a channel op or higher to " << what << " channel mode l (limit).\r\n";
		return false;
	}
	
	if (flag == "-l")
	{
		_Limit = 100;
		msg << ":" << client->getNickname() << "!" << client->getUsername() << "@" << client->getHostname() << " MODE " << _Name << " :" << flag << "\r\n";
		return true;
	}

	if (str.empty())
	{
		msg << ":" << Server::getHostname() << " 696 " << client->getNickname() << " " << _Name << " l * :You must specify a parameter for the limit mod. Syntax: <limit>.\r\n";
		return false;
	}

	std::stringstream count(str);
	count >> _Limit;
	if (count.fail() || _Limit < 0)
	{
		msg << ":" << Server::getHostname() << " 696 " << client->getNickname() << " " << _Name << " l * :Invalid limit value.\r\n";
		return false;
	}
	return true;
}
