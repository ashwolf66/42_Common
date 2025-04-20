#include "PhoneBook.hpp"

PhoneBook ::PhoneBook(void)
{
	this->i = 0;
}

PhoneBook ::~PhoneBook(void)
{
	std::cout << "END" << std::endl;
}

void PhoneBook::add(void)
{
	std::string str;

	str = "\0";
	if (this->i > 7)
		this->i = 0;
	while (str == "\0")
	{
		std::cout << "First Name(Can't Empty) : ";
		if (std::getline(std::cin, str) && str != "\0")
			this->contact[this->i % 8].SetFirst(str);
	}
	str = "\0";
	while (str == "\0")
	{
		std::cout << "Last Name(Can't Empty) : ";
		if (std::getline(std::cin, str) && str != "\0")
			this->contact[this->i % 8].SetLast(str);
	}
	str = "\0";
	while (str == "\0")
	{
		std::cout << "Nick Name(Can't Empty) : ";
		if (std::getline(std::cin, str) && str != "\0")
			this->contact[this->i % 8].SetNick(str);
	}
	str = "\0";
	while (str == "\0")
	{
		std::cout << "Phone Num(Can't Empty) : ";
		if (std::getline(std::cin, str) && str != "\0")
			this->contact[this->i % 8].SetNum(str);
	}
	str = "\0";
	while (str == "\0")
	{
		std::cout << "First Secret(Can't Empty) : ";
		if (std::getline(std::cin, str) && str != "\0")
			this->contact[this->i % 8].SetSecret(str);
	}
	this->i++;
}

void	PhoneBook::search(void)
{
	std::string	str;

	std::cout << "> Index(Exit : 0) : ";
	std::getline(std::cin, str);
	while (1)
	{
		if (str.size() == 1 && str[0] == '0')
			return ;
		if (str.size() != 1 || str[0] < '1' || str[0] > '8')
		{
			std::cout << "Invalid Index!!" << std::endl;
			std::cout << "> Index(Exit : 0) : ";
			std::getline(std::cin, str);
			continue ;
		}
		else if (this->contact[str[0] - 1 - '0'].GetFirst().size() != 0)
			break ;
	}
	this->PrintIndex(this->contact[str[0] - 1 - '0']);
}

int		PhoneBook::PhoneList(Contact contact[8])
{
	char		chr;
	int			i;
	std::string	str;

	chr = '1';
	i = 0;
	std::cout << "|----------|----------|----------|----------|" << std::endl;
	std::cout << "|     Index|     Fisrt|      Last|      Nick|" << std::endl;
	std::cout << "|----------|----------|----------|----------|" << std::endl;
	while (chr <= '8')
	{
		if (contact[chr - 1 - '0'].GetFirst().size())
		{
			str = chr;
			str = ParseLen(str, 10);
			std::cout << "|" << PrintListIndex(10 - str.size()) << str;
			str = ParseLen(contact[chr - 1 - '0'].GetFirst(), 10);
			std::cout << "|" << PrintListIndex(10 - str.size()) << str;
			str = ParseLen(contact[chr - 1 - '0'].GetLast(), 10);
			std::cout << "|" << PrintListIndex(10 - str.size()) << str;
			str = ParseLen(contact[chr - 1 - '0'].GetNick(), 10);
			std::cout << "|" << PrintListIndex(10 - str.size()) << str;
			std::cout << "|" << std::endl;
		}
		i++;
		chr++;
	}
	std::cout << std::endl;
	return (i);
}

std::string	PhoneBook::ParseLen(std::string str, int len)
{
	if (str.size() > len)
	{
		str.resize(len);
		str[str.size() - 1] = '.';
	}
	return (str);
}

std::string	PhoneBook::PrintListIndex(int len)
{
	std::string	str;
	int			i;

	i = 0;
	while (i < len)
		str.append(" ");
	return (str);
}

void	PhoneBook::PrintIndex(Contact contact)
{
	std::cout << "First : " << contact.GetFirst() << std::endl;
	std::cout << "Last : " << contact.GetLast() << std::endl;
	std::cout << "Nick : " << contact.GetNick() << std::endl;
	std::cout << "Num : " << contact.GetNum() << std::endl;
	std::cout << "Dark Secret : " << contact.GetSecret() << std::endl;
}