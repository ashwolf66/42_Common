/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:34:49 by jacha             #+#    #+#             */
/*   Updated: 2025/04/27 14:34:51 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie()
{
}
Zombie::Zombie(std::string name)
{
	this->_name = name;
}

Zombie::~Zombie()
{
	std::cout << "Zombie " << this->_name << " is Die" << std::endl;
}

void	Zombie::announce()
{
	std::cout << this->_name << " : BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::SetName(std::string name)
{
	this->_name = name;
	std::cout << "Zombie " << this->_name << " is Gen" << std::endl;
}