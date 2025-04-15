#include <iostream>

int	main(int argc, char **argv)
{
	std::string	Str;

	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	else if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			std::string temp = argv[i];
			for (int j = 0; j < temp.size(); j++)
			{
				std::cout << (char)toupper(temp[j]);
			}
		}	
		std::cout << std::endl;
	}
	return (0);
}
