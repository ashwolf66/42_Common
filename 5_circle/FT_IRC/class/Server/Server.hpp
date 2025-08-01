#ifndef SERVER_HPP
# define SERVER_HPP

#include "../Client/Client.hpp"

class ClientManager;
class ChannelManager;

class Server : public Socket
{
private:
	static int					epfd;
	static bool					exit_flag;
	static std::string			hostname;
	static std::time_t			time;
	int							port;
	std::string					password;
	epoll_event					*events;
	char						buffer[BUFFER_SIZE];
	ClientManager*				cm;
	ChannelManager*				ch_manager;

 public:
	Server(int port, char *password);
	~Server();
				
	static int							get_epfd();
	static void							set_epfd(int epfd);

	static bool							get_exit_flag();
	static void							set_exit_flag(bool flag);

	static std::string					getHostname();
	static time_t						getTime();
	bool								initEpoll();
	bool								initServerSocket();
	bool								setServerSocket();
	void								handle_event();
		
	int									wait();
	void								readClient(epoll_event &event);
		
	bool								check_client_connection(epoll_event &event);
	bool								check_client_disconnection(epoll_event &event);
	bool								check_client_readable(epoll_event &event);
	
	t_str_pair							split_prev(std::string &msg);
	std::vector<std::string>			split_mode(std::string &modes);
	std::vector<std::string> 			split(const std::string &str, char delimiter);
	
	int									handle_cmd(t_str_pair &cmd_pair, Client *client);
	void								loop();

	void								send_registered(Client *client);
	void								send_not_registered(Client *client);

	void								handle_pass(std::string &str, Client *client);
	void								handle_nick(std::string &str, Client *client);
	void								handle_user(std::string &str, Client *client);
	void								handle_join(std::string &str, Client *client);
	void								handle_privmsg(std::string &str, Client *client);
	void								handle_kick(std::string &str, Client *client);
	void								handle_invite(std::string &str, Client *client, ClientManager *cm);
	void								handle_topic(std::string &str, Client *client);
	void								handle_mode(std::string &str, Client *client);
	void								handle_ping(std::string &str, Client *client);
	void								handle_quit(std::string &str, Client *client);
	void								handle_part(std::string &str, Client *client);
	void								handle_whois(std::string &str, Client *client);
	void								handle_who(std::string &str, Client *client);

	void								user_mode(Client *client, std::vector<std::string> &modes);
};

#endif