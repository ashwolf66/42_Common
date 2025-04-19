#ifndef PHONEBOOK_H
# define PHONEBOOK_H

#include "MyAwesomePhoneBook.hpp"

class PhoneBook
{
private:
	Contact contact[8];
	int i;

public:
	PhoneBook(void);
	~PhoneBook(void);
	void	add(void);
	void	search(void);
};

#endif