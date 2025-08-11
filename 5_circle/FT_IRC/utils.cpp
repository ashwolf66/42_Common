#include "ft_irc.hpp"

t_str_pair	split_prev(std::string &msg)
{
	t_str_pair res;
	size_t pos;
	if (msg == "")
		return res;

	pos = msg.find('\r');
	if (pos != std::string::npos)
		msg.erase(pos);

	pos = msg.find(' ');
	if (pos != std::string::npos)
	{
		res.first = msg.substr(0, pos);
		res.second = msg.substr(pos + 1);
	}
	else
	{
		res.first = msg;
		res.second = "";
	}
	return res;
}

std::vector<std::string> split(const std::string &str, const char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream stream(str);
	std::string token;

	while (std::getline(stream, token, delimiter))
	{
		if (!token.empty())
			tokens.push_back(token);
	}
	return tokens;
}

std::string get_front(const std::string &str, const char delimiter)
{
	size_t pos = str.find(delimiter);
	if (pos != std::string::npos)
	{
		std::string front = str.substr(0, pos);
		return front;
	}
	return str;
}
