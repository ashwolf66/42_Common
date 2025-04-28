/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:10:42 by jacha             #+#    #+#             */
/*   Updated: 2025/04/28 10:10:43 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Weapon.hpp"

Weapon::Weapon()
{

}

Weapon::Weapon(std::string type)
{
	setType(type);
}

Weapon::~Weapon()
{

}

void	Weapon::setType(std::string type)
{
	this->_type = type;
}

const std::string	&Weapon::getType() const
{
	return (this->_type);
}