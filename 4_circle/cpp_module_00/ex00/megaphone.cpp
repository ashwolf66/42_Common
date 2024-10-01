#include <iostream>

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	else if (argc > 1)
	{
		int	i = 1;
		for (i; i < argc; i++)
		{
			std::string templ(argv[i]);
			for (int j = 0; j < templ.size(); j++)
			{
				std::cout << (char)toupper(templ[j]);
			}
			std::cout << " ";
		}	
		std::cout << std::endl;
	}
	return (0);
}
