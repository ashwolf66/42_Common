/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:38:53 by jacha             #+#    #+#             */
/*   Updated: 2025/05/16 07:38:54 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(std::string const &type) : _type(type)
{
}

AMateria::~AMateria()
{
}

std::string const &AMateria::getType() const
{
	return _type;
}

void AMateria::use(ICharacter &target)
{
	target.getName();
}
