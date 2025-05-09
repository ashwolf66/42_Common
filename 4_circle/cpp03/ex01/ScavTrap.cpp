#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("jacha")
{
	this->_HitPoint = 100;
	this->_EnergyPoint = 50;
	this->_AttackDamage = 20;
	std::cout << "ScavTrap Default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->_HitPoint = 100;
	this->_EnergyPoint = 50;
	this->_AttackDamage = 20;
    std::cout << "ScavTrap Name constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
    std::cout << "ScavTrap Copy constructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
    ClapTrap::operator=(other);
    std::cout << "ScavTrap Assignment operator called" << std::endl;
    return *this;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap Destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
    if (this->_HitPoint > 0 && this->_EnergyPoint > 0)
	{
		this->_EnergyPoint--;
		std::cout << "ScavTrap " << this->_name << " attacks " << target << ", causing ";
		std::cout << this->_AttackDamage << " point of damage !" << std::endl;
	}
	else if (this->_EnergyPoint == 0)
		std::cout << "ScavTrap " << this->_name << " can't attack(Energy : " << this->_EnergyPoint << ")" << std::endl;
	else if (this->_HitPoint == 0)
		std::cout << "ScavTrap " << this->_name << " is already dead" << std::endl;
	return ;
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode!" << std::endl;
}
