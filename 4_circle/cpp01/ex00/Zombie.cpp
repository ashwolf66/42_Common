/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:51:41 by jacha             #+#    #+#             */
/*   Updated: 2025/04/26 14:51:45 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name)
{
	this->_name = name;
	std::cout << "Zombie " << this->_name << " is Gen" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << "Zombie " << this->_name << " is Die" << std::endl;
}

void	Zombie::announce()
{
	std::cout << this->_name << " : BraiiiiiiinnnzzzZ..." << std::endl;
}