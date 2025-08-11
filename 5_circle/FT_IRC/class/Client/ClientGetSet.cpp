#include "Client.hpp"

bool Client::getIsPasswordValid()
{
	return isPasswordValid;
}

void Client::setIsPasswordValid(bool flag)
{
	this->isPasswordValid = flag;
}

bool Client::getIsRegistered()
{
	return isRegistered;
}

void Client::setIsRegistered(bool connected)
{
	this->isRegistered = connected;
}

std::string& Client::getNickname()
{
	return nickname;
}

void Client::setNickname(std::string &nick)
{
	this->nickname = nick;
}

std::string& Client::getUsername()
{
	return username;
}

void Client::setUsername(std::string &user)
{
	this->username = user;
}

std::string& Client::getHostname()
{
	return hostname;
}

bool Client::setHostname()
{
	hostent* hent = gethostbyaddr(&addr.sin_addr, sizeof(addr.sin_addr), AF_INET);

	if (hent == NULL || hent->h_name == NULL || std::string(hent->h_name) != "localhost")
	{
		std::cerr << "Failed to get hostname for IP: " << Ip << std::endl;
		hostname = Ip;
		return true;
	}
	
	hostname = hent->h_name;
	return false;
}

std::string &Client::getServername()
{
	return servername;
}

void Client::setServername(std::string &server)
{
	this->servername = server;
}

std::string& Client::getRealname()
{
	return realname;
}

void Client::setRealname(std::string &real)
{
	this->realname = real;
}

bool Client::getIsInvisible()
{
	return isInvisible;
}

void Client::setIsInvisible(bool invisible)
{
	this->isInvisible = invisible;
}
