#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("jacha")
{
	this->setHitPoint(100);
	this->setEnergyPoint(50);
	this->setAttackDamage(20);
	std::cout << "ScavTrap Default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->setHitPoint(100);
	this->setEnergyPoint(50);
	this->setAttackDamage(20);
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
    std::cout << "ScavTrap " << this->getName() << " Destructor called" << std::endl;
}

void ScavTrap::attack(const std::string &target)
{
	if (this->getHitPoint() > 0 && this->getEnergyPoint() > 0)
	{
		this->setEnergyPoint(this->getEnergyPoint() - 1);
		std::cout << "ScavTrap " << this->getName() << " attacks " << target << ", causing ";
		std::cout << this->getAttackDamage() << " point of damage!!! Energy is lost 1(Energy" << this->getEnergyPoint() << ")"  << std::endl;
	}
	else if (this->getEnergyPoint() == 0)
		std::cout << "ScavTrap " << this->getName() << " can't attack (Energy : " << this->getEnergyPoint() << ")" << std::endl;
	else if (this->getHitPoint() == 0)
		std::cout << "ScavTrap " << this->getName() << " is already dead" << std::endl;
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << this->getName() << " is now in Gate keeper mode!" << std::endl;
}
