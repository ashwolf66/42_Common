#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "../Socket/Socket.hpp"

class Channel;

class Client : public Socket
{
private:
	bool			isPasswordValid;
	bool			isRegistered;
	std::string		nickname;
	std::string		username;
	std::string		hostname;
	std::string		servername;
	std::string		realname;
	bool			isInvisible;
	std::vector<Channel *> channels;

public:
	Client(int serv_fd, int epfd);
	~Client();

	bool			getIsPasswordValid();
	void			setIsPasswordValid(bool flag);

	bool			getIsRegistered();
	void			setIsRegistered(bool connected);

	std::string&	getNickname();
	void			setNickname(std::string &nick);

	std::string&	getUsername();
	void			setUsername(std::string &user);

	std::string&	getHostname();
	bool			setHostname();

	std::string&	getServername();
	void			setServername(std::string &server);

	std::string&	getRealname();
	void			setRealname(std::string &real);

	bool			getIsInvisible();
	void			setIsInvisible(bool invisible);

	void			addChannel(Channel *channel);
	void			leave_channels(Channel *channel);
	bool			isInChannel(std::string &channel);
	void			quit(const std::string &msg);

	void			lookingHostname();

	void			printTime();
	void			sendMessage(std::ostringstream &message);
	void			print_recv(std::string back);
};

#endif