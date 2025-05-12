/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:27:24 by jacha             #+#    #+#             */
/*   Updated: 2025/05/12 15:11:08 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("jacha"), _HitPoint(10), _EnergyPoint(10), _AttackDamage(0)
{
	std::cout << "ClapTrap Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _HitPoint(10), _EnergyPoint(10), _AttackDamage(0)
{
	std::cout << "ClapTrap Name constructor called. Name is " << this->_name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
{
	std::cout << "ClapTrap Copy constructor called" << std::endl;
	*this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "ClapTrap Copy assignation operator called" << std::endl;
	if (this != &other)
	{
		this->_name = other._name;
		this->_HitPoint = other._HitPoint;
		this->_EnergyPoint = other._EnergyPoint;
		this->_AttackDamage = other._AttackDamage;
	}
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap Destructor " << this->_name << " called" << std::endl;
}

void	ClapTrap::attack(const std::string& target)
{
	if (this->_HitPoint > 0 && this->_EnergyPoint > 0)
	{
		this->_EnergyPoint--;
		std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing ";
		std::cout << this->_AttackDamage << " point of damage!!! Energy is lost 1(Energy" << this->_EnergyPoint << ")" << std::endl;
	}
	else if (this->_EnergyPoint == 0)
		std::cout << "ClapTrap " << this->_name << " can't attack(Energy : " << this->_EnergyPoint << ")" << std::endl;
	else if (this->_HitPoint == 0)
		std::cout << "ClapTrap " << this->_name << " is already dead" << std::endl;
	return ;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_HitPoint > 0)
	{
		this->_HitPoint -= amount;
		std::cout << "ClapTrap " << this->_name << " take damage " << amount << std::endl;
		if (this->_HitPoint <= 0)
		{
			this->_HitPoint = 0;
			std::cout << "ClapTrap " << this->_name << " health is " << this->_HitPoint << ". Die.." << std::endl;
			return ;
		}
	}
	else
	{
		std::cout << "ClapTrap " << this->_name << " is already dead" << std::endl;
		return ;
	}
	std::cout << "ClapTrap " << this->_name << " health is " << this->_HitPoint << "." << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_HitPoint > 0 && this->_EnergyPoint > 0)
	{
		this->_HitPoint += amount;
		this->_EnergyPoint--;
		std::cout << "ClapTrap " << this->_name << " is repaited health " << amount << "!!! Energy is lost 1(Energy" << this->_EnergyPoint << ")" << std::endl;
		std::cout << "ClapTrap " << this->_name << " Health : " << this->_HitPoint << std::endl;
	}
	else if (this->_HitPoint == 0)
	{
		std::cout << "ClapTrap " << this->_name << " is already Die.." << std::endl;
		return ;
	}
	else if (this->_EnergyPoint == 0)
	{
		std::cout << "ClapTrap " << this->_name << " can't repair(Energy : " << this->_EnergyPoint << ")" << std::endl;
	}
	return ;
}
