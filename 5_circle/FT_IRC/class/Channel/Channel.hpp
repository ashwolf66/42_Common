#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../Client/Client.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../Server/Server.hpp"
#include "../Socket/Socket.hpp"

class Channel
{
private:
	std::list<Client *>	_OpClients;
	std::list<Client *>	_ReClients;
	std::list<Client *>	_InviteList;
	std::time_t				_InitTimeToServer;
	std::time_t				_InitTimeToTopic;
	std::string				_Name;
	std::string				_Password;
	std::string				_Topic;
	std::string				_TopicWriter;
	size_t					_Limit;
	bool					_IFlag;
	bool					_TFlag;

public:
	Channel(std::string name);
	~Channel();

	std::string &getName();

	bool	FindOpClient(Client *client);
	bool	FindOpClient(Client * client, std::list<Client *>::iterator &it);
	bool	FindOpClient(const std::string &nick, std::list<Client *>::iterator &it);

	bool	FindReClient(Client * client, std::list<Client *>::iterator &it);
	bool	FindReClient(const std::string &nick, std::list<Client *>::iterator &it);

	bool	FindClient(Client *client, std::list<Client *>::iterator &it, std::list<Client *>**where);
	bool	FindClient(const std::string &nick, std::list<Client *>::iterator &it, std::list<Client *>**where);

	bool	isInviteClient(Client *client);

	void	DisconnetionClient(Client *client, const std::string &msg);

	void	broadcast(Client *client, std::ostringstream &msg);
	void	writeJoinedClientNameList(Client *client, std::ostringstream &msg);
	void	join(Client *client, std::string &password, std::ostringstream &msg);
	void	privmsg(Client *client, std::string &msg);
	void	kick(Client *client, std::string nick, std::string reason);
	void	invite(Client *client, std::string nick, ClientManager *clientManager);
	void	topic(Client *client, std::string topic);

	bool	setFlag(Client *client, std::string &flag, char &toggle_sign, std::vector<std::string>::iterator &param_it, std::vector<std::string> &params, std::ostringstream &msg);
	bool	selectMode(Client *client, std::string &flag, const std::string &param, std::ostringstream &msg);
	void	mode(Client *client, std::vector<std::string> flag, std::vector<std::string> str);
	void	part(Client *client, std::string reason);

	bool	isInvalidModeFlag(std::string &flag);
	bool	isUsedParamMode(const std::string &flag);
	bool	I_Option(Client *client, std::string flag, std::ostringstream &msg);
	bool	T_Option(Client *client, std::string flag, std::ostringstream &msg);
	bool	K_Option(Client *client, std::string flag, std::string str, std::ostringstream &msg);
	bool	O_Option(Client *client, std::string flag, std::string str, std::ostringstream &msg);
	bool	L_Option(Client *client, std::string flag, std::string str, std::ostringstream &msg);
};

#endif