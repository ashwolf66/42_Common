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
	this->name = name;
	std::cout << "Zombie " << name << " is Gen" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << "Zombie " << name << " is Die" << std::endl;
}

void	Zombie::announce()
{
	std::cout << name << " : BraiiiiiiinnnzzzZ..." << std::endl;
}