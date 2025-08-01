#include "Server.hpp"
#include "../ClientManager/ClientManager.hpp"
#include "../ChannelManager/ChannelManager.hpp"


std::time_t	Server::time = 0;
int			Server::epfd = -1;
bool		Server::exit_flag = false;
std::string	Server::hostname = "ft.irc.com";

Server::Server(int port, char* password) : port(port), password(password), cm(new ClientManager()), ch_manager(new ChannelManager())
{
	fd = -1;

	std::cout << "IRC server starting on port " << port << " with password '" << password << "'." << std::endl;

	if (initServerSocket() || setServerSocket())
		throw std::runtime_error("Failed to initialize server socket");

	events = new epoll_event[MAX_CLIENTS];
}

Server::~Server()
{
	delete cm;
	delete ch_manager;
	delete[] events;
	if (fd >= 0)
	{
		if (epfd >= 0)
		{
			if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) < 0)
				std::cerr << "Failed to remove server socket from epoll" << std::endl;
		}
		close(fd);
	}
	if (epfd >= 0)
	{
		close(epfd);
		epfd = -1;
	}
	std::cout << "IRC server stopped." << std::endl;
}

bool	Server::initEpoll()
{
	epoll_event event;

	Server::epfd = epoll_create1(0);
	if (epfd < 0)
	{
		close(fd);
		std::cerr << "Failed to create epoll instance." << std::endl;
		return true;
	}

	event.events = EPOLLIN;
	event.data.ptr = this;

	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event) < 0)
	{
		close(fd);
		close(epfd);
		std::cerr << "Failed to add server socket to epoll" << std::endl;
		return true;
	}
	return false;
}

bool Server::initServerSocket()
{
	fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd < 0)
	{
		std::cerr << "Failed to create socket." << std::endl;
		return true;
	}

	int flag = 1;
	socklen_t optlen = sizeof(flag);
	if (set_flag_fd(fd, O_NONBLOCK))
	{
		close(fd);
		std::cerr << "Failed to set server socket to non-blocking mode." << std::endl;
		return true;
	}
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, optlen) < 0)
	{
		close(fd);
		std::cerr << "Failed to set socket options." << std::endl;
		return true;
	}

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
 	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (setIp())
	{
		close(fd);
		std::cerr << "Failed to set server IP address." << std::endl;
		return true;
	}

	return initEpoll();
}

bool	Server::setServerSocket()
{
	if (bind(fd, (sockaddr *)&addr, sizeof(addr)) < 0)
	{
		close(fd);
		std::cerr << "Failed to bind socket to port " 
			<< port << std::endl;
		return true;
	}

	if (listen(fd, MAX_CLIENTS) < 0)
	{
		close(fd);
		std::cerr << "Failed to listen on port " << port << "." << std::endl;
		return true;
	}

	std::cout << "IRC server is listening on IP "
				<< getIp() << ":"
				<< getPort() << std::endl;
	return false;
}

void	Server::readClient(epoll_event &event)
{
	Client *client = static_cast<Client *>(event.data.ptr);
	std::string line = "";
	while (true)
	{
		std::memset(buffer, 0, BUFFER_SIZE);
		ssize_t bytes_read = recv(client->getFd(), buffer, BUFFER_SIZE, 0);
		if (bytes_read < 0)
		{
			std::cerr << bytes_read << " " << strerror(errno) << std::endl;
			cm->del(event);
			return;
		}
		line += buffer;
		if (bytes_read == 0 || line.find("\r\n") != std::string::npos)
			break;
	}

	if (line.find("\r\n") == std::string::npos)
		return;

	std::vector<std::string> lines = split(line, '\n');
	for (size_t i = 0; i < lines.size(); i++)
	{
		t_str_pair cmd_pair = split_prev(lines[i]);

		client->print_recv(lines[i]);
		std::transform(cmd_pair.first.begin(), cmd_pair.first.end(), cmd_pair.first.begin(), ::toupper);
		handle_cmd(cmd_pair, client);
	}
}

int	Server::wait()
{
	int num_events = epoll_wait(epfd, events, MAX_CLIENTS, -1);
	if (num_events < 0)
	{
		if (errno != EINTR)
		{
			std::cerr << "Epoll wait error: " << strerror(errno) << std::endl;
			throw std::runtime_error("Epoll wait failed");
		}
		return -1;
	}
	return num_events;
}

void	Server::handle_event()
{
	int num_events = wait();
	if (num_events < 0)
		return;
	for (int i = 0; i < num_events; i++)
	{
		if (check_client_connection(events[i]))
			cm->add(fd);
		else if (check_client_disconnection(events[i]))
			cm->del(events[i]);
		else if (check_client_readable(events[i]))
			readClient(events[i]);
		else
		{
			std::cerr << "Unknown event type." << std::endl;
		}
	}
}

void Server::loop()
{
	while (Server::get_exit_flag() == false)
	{
		try { handle_event(); }
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			break;
		}
	}
}