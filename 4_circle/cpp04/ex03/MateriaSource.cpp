/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:39:15 by jacha             #+#    #+#             */
/*   Updated: 2025/05/16 07:39:16 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; ++i)
		_templates[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource &other)
{
	*this = other;
}

MateriaSource &MateriaSource::operator=(const MateriaSource &other)
{
	if (this != &other)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (_templates[i])
				delete _templates[i];
			_templates[i] = other._templates[i] ? other._templates[i]->clone() : NULL;
		}
	}
	return *this;
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; ++i)
		delete _templates[i];
}

void MateriaSource::learnMateria(AMateria *m)
{
	if (!m)
		return;
	for (int i = 0; i < 4; ++i)
	{
		if (!_templates[i])
		{
			_templates[i] = m->clone();
			std::cout << "MateriaSource learned: " << m->getType() << std::endl;
			delete m;
			return;
		}
	}
	std::cout << "MateriaSource memory full. Cannot learn more materias." << std::endl;
	delete m;
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4; ++i)
	{
		if (_templates[i] && _templates[i]->getType() == type)
		{
			std::cout << "MateriaSource created materia: " << type << std::endl;
			return _templates[i]->clone();
		}
	}
	std::cout << "MateriaSource couldn't find materia: " << type << std::endl;
	return NULL;
}
