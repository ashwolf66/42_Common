/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:11:10 by jacha             #+#    #+#             */
/*   Updated: 2025/05/12 15:11:11 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("jacha_clap_name"), ScavTrap(), FragTrap(), _name("jacha")
{
	std::cout << "DiamondTrap Default constructor called" << std::endl;
	this->_HitPoint = FragTrap::_HitPoint;
	this->_EnergyPoint = ScavTrap::_EnergyPoint;
	this->_AttackDamage = FragTrap::_AttackDamage;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other) : ClapTrap(other), ScavTrap(other), FragTrap(other)
{
	std::cout << "DiamondTrap Copy constructor called" << std::endl;
	*this = other;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other)
{
	std::cout << "DiamondTrap Copy assignation operator called" << std::endl;
	if (this != &other)
	{
		this->_name = other._name;
		FragTrap::_HitPoint = other._HitPoint;
		ScavTrap::_EnergyPoint = other._EnergyPoint;
		FragTrap::_AttackDamage = other._AttackDamage;
	}
	return (*this);
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap Destructor " << this->_name << " called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(), FragTrap(), _name(name)
{
	std::cout << "DiamondTrap Name constructor called. Name is " << this->_name << std::endl;
	this->_HitPoint = FragTrap::_HitPoint;
	this->_EnergyPoint = ScavTrap::_EnergyPoint;
	this->_AttackDamage = FragTrap::_AttackDamage;
}

void DiamondTrap::whoAmI()
{
	std::cout << "ClapTrap name is " << ClapTrap::_name << std::endl;
	std::cout << "DiamondTrap name is " << this->_name << std::endl;
}
