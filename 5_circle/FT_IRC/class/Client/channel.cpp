#include "Client.hpp"
#include "../Channel/Channel.hpp"

void Client::addChannel(Channel *channel)
{
	if (std::find(channels.begin(), channels.end(), channel) == channels.end())
		channels.push_back(channel);
}

void Client::leave_channels(Channel *channel)
{
	for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if ((*it) == channel)
		{
			channels.erase(it);
			return;
		}
	}
}

bool Client::isInChannel(std::string &channel)
{
	for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if ((*it)->getName() == channel)
			return true;
	}
	return false;
}

void Client::quit(const std::string &msg)
{
	std::ostringstream o_msg;

	o_msg << "ERROR :Closing Link: ("
		<< getUsername() << "@" << getIp()
		<< ") [Quit: " << msg << "]" << "\r\n";
	sendMessage(o_msg);
	for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
		(*it)->DisconnetionClient(this, msg);

	channels.clear();
}