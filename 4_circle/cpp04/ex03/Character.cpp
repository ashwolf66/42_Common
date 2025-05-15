/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:38:57 by jacha             #+#    #+#             */
/*   Updated: 2025/05/16 07:38:59 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string const &name) : _name(name), _unequippedCount(0)
{
	std::cout << "Character created: " << name << std::endl;
	for (int i = 0; i < 4; ++i)
		_inventory[i] = NULL;
	for (int i = 0; i < 100; ++i)
		_unequipped[i] = NULL;
}

Character::Character(const Character &other)
{
	*this = other;
}

Character &Character::operator=(const Character &other)
{
	if (this != &other)
	{
		_name = other._name;

		for (int i = 0; i < 4; ++i)
		{
			if (_inventory[i])
				delete _inventory[i];
			_inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : NULL;
		}

		for (int i = 0; i < _unequippedCount; ++i)
		{
			delete _unequipped[i];
			_unequipped[i] = NULL;
		}
		_unequippedCount = 0;
	}
	return *this;
}

Character::~Character()
{
	for (int i = 0; i < 4; ++i)
		delete _inventory[i];

	for (int i = 0; i < _unequippedCount; ++i)
		delete _unequipped[i];

	std::cout << "Character destroyed: " << _name << std::endl;
}

std::string const &Character::getName() const
{
	return _name;
}

void Character::equip(AMateria *m)
{
	if (!m)
		return;
	for (int i = 0; i < 4; ++i)
	{
		if (!_inventory[i])
		{
			_inventory[i] = m;
			std::cout << _name << " equips materia at slot " << i << std::endl;
			return;
		}
	}
	std::cout << _name << "'s inventory is full. Cannot equip materia." << std::endl;
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4 || !_inventory[idx])
		return;

	if (_unequippedCount < 100)
		_unequipped[_unequippedCount++] = _inventory[idx];

	_inventory[idx] = NULL;
	std::cout << _name << " unequips materia from slot " << idx << std::endl;
}

void Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= 4 || !_inventory[idx])
		return;

	_inventory[idx]->use(target);
}
