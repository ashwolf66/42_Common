#include "ft_irc.hpp"
#include "class/Server/Server.hpp"

void	sighandler(int sig)
{
	(void) sig;
	std::cout << "\r";
	Server::set_exit_flag(true);
}

void	setup(int argc, char **argv, int &port, char **password)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		std::exit(1);
	}
	
	port = std::atoi(argv[1]);
	if (port <= 0 || port > 65535)
	{
		std::cerr << "Error: Port must be a number between 1 and 65535." << std::endl;
		std::exit(1);
	}
	*password = argv[2];

	if (std::signal(SIGINT, sighandler) == SIG_ERR)
	{
		std::cerr << "Error: Unable to set signal handler." << std::endl;
		std::exit(1);
	}
}

int	main(int argc, char **argv)
{
	int					port;
	char*				password;
	
	setup(argc, argv, port, &password);
	Server *server;

	try { server = new Server(port, password); }
	catch (const std::exception &e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return 1;
	}

	server->loop();
	delete server;
}