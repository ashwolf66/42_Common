/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:00:00 by jacha             #+#    #+#             */
/*   Updated: 2025/04/23 17:00:02 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact :: Contact(void)
{

}

Contact :: ~Contact(void)
{

}

std::string Contact::GetFirst(void)
{
	return (this->First);
}

std::string Contact::GetLast(void)
{
	return (this->Last);
}

std::string Contact::GetNick(void)
{
	return (this->Nick);
}

std::string Contact::GetNum(void)
{
	return (this->Num);
}

std::string Contact::GetSecret(void)
{
	return (this->Secret);
}

void	Contact::SetFirst(std::string str)
{
	this->First = str;
}
void	Contact::SetLast(std::string str)
{
	this->Last = str;
}
void	Contact::SetNick(std::string str)
{
	this->Nick = str;
}
void	Contact::SetNum(std::string str)
{
	this->Num = str;
}
void	Contact::SetSecret(std::string str)
{
	this->Secret = str;
}
