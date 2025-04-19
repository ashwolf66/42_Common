#include "MyAwesomePhoneBook.hpp"

int main(int argc, char **argv)
{
	PhoneBook	Phone;
	std::string	Str;

	while(Str != "EXIT" && Str != "exit")
	{
		std::cout << "Typeing ADD/SEARCH/EXIT" << std::endl;
		std::getline(std::cin, Str);
		if (Str == "ADD" || Str == "add")
		{

		}
		else if (Str == "SEARCH" || Str == "search")
		{

		}
		else
			continue ;
	}
	return (0);
}