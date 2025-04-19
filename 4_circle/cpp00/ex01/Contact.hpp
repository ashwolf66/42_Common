#ifndef CONTACT_H
# define CONTACT_H

#include "MyAwesomePhoneBook.hpp"

class Contact
{
private:
	std::string First;
	std::string Last;
	std::string Nick;
	std::string Num;
	std::string Secret;

public:
	Contact(void);
	~Contact(void);
	std::string	GetFirst(void);
	std::string	GetLast(void);
	std::string	GetNick(void);
	std::string	GetNum(void);
	std::string	GetSecret(void);
	void	SetFirst(std::string GetFirst);
	void	SetLast(std::string GetLast);
	void	SetNick(std::string GetNick);
	void	SetNum(std::string GetNum);
	void	SetSecret(std::string GetSecret);
};

#endif