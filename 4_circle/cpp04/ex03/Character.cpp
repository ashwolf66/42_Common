#include "Character.hpp"

Character::Character() : _name("Defult")
{
}

Character::Character(std::string name) : _name(name)
{
}

std::string const &Character::getName() const
{
}

void Character::equip(AMateria *m)
{
}

void Character::unequip(int idx)
{
}

void Character::use(int idx, ICharacter &target)
{
}