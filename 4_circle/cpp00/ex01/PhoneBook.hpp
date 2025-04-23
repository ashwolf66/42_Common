/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:00:12 by jacha             #+#    #+#             */
/*   Updated: 2025/04/23 17:00:19 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H

#include <iostream>
#include <string>
#include "Contact.hpp"

class PhoneBook
{
private:
	Contact contact[8];
	int i;

public:
	PhoneBook(void);
	~PhoneBook(void);
	void		add(void);
	void		search(void);
	void		PrintIndex(Contact contact);
	int			PhoneList(Contact contact[8]);
	std::string	ParseLen(std::string str, int len);
	std::string	PrintListIndex(int len);
};

#endif
