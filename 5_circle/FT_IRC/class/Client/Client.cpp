#include "Client.hpp"
#include "Client_create_error/Client_create_error.hpp"
#include "../Server/Server.hpp"
#include "../Channel/Channel.hpp"

Client::Client(int serv_fd, int epfd)
:	isPasswordValid(false), isRegistered(false), 
	nickname("*"), username("*"), hostname("*"), realname("*"),
	isInvisible(false)
{
	socklen_t	addr_len = sizeof(addr);
	
	fd = accept(serv_fd, (sockaddr *)&addr, &addr_len);	
	if (fd < 0)
		throw ClientCreateError("Failed to accept client connection");

	if (set_flag_fd(fd, O_NONBLOCK))
	{
		close(fd);
		throw ClientCreateError("Failed to set client socket to non-blocking mode");
	}

	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET | EPOLLRDHUP | EPOLLHUP | EPOLLERR;
	ev.data.ptr = this;
	
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) < 0)
	{
  		close(fd);
  		throw ClientCreateError("Failed to add client socket to epoll");
	}

	if (setIp())
	{
		close(fd);
		throw ClientCreateError("Failed to set client IP address");
	}
	lookingHostname();
}

Client::~Client()
{
	if (epoll_ctl(Server::get_epfd(), EPOLL_CTL_DEL, fd, NULL) < 0)
		std::cerr << "Failed to remove client socket from epoll" << std::endl;
	close(fd);
}

void Client::lookingHostname()
{
	std::ostringstream msg;

	msg << ":" << Server::getHostname() << " NOTICE * :*** Looking up your hostname...\r\n";
	sendMessage(msg);
	msg.str("");

	if (setHostname())
	{
		msg << ":" << Server::getHostname() << " NOTICE * :*** Your hostname does not match up with your IP address; using your IP address ("
			<< getIp() << ") instead.\r\n";
		sendMessage(msg);
		return;
	}

	msg << ":" << Server::getHostname() << " NOTICE * :*** Found your hostname (" << hostname << ")\r\n";
	sendMessage(msg);
}

void Client::printTime()
{
	char buffer[26];
	std::time_t current_time = Server::getTime();
	std::tm *tm_info = std::localtime(&current_time);
	if (!tm_info)
		throw std::runtime_error("Failed to convert time to local time");
	if (!std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info))
		throw std::runtime_error("Failed to format time");
	std::cout << "\n\033[1;33m[" << buffer << "]\033[0m ";

}

void Client::sendMessage(std::ostringstream &msgStream)
{
	std::string msg = msgStream.str();
	std::string out_msg = msg.substr(0, msg.find_last_of("\r\n"));

	printTime();
	if (send(fd, msg.c_str(), msg.length(), 0) < 0)
	{
		std::cerr << "\033[1;31mFailed to send message to client at "
			<< getIp() << ":"
			<< getPort() << "\033[0m $ "
			<< out_msg << std::endl;
		std::cerr << "Error: " << fd << " : " << strerror(errno) << std::endl;
	}
	else
	{
		std::cout << "  \033[1;35mTo \033[0m\033[1;32m"
			<< getIp() << ":"
			<< getPort() << "\033[0m $ "
			<< out_msg << "\n";
	}
}

void	Client::print_recv(std::string back)
{
	printTime();
	std::cout 
		<< "\033[1;34mFrom \033[0m\033[1;32m"
		<< getIp() << ":"
		<< getPort()  << "\033[0m $ \033[1;44m"
		<< back << "\033[0m\n";
}