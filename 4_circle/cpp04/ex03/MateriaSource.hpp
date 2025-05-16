/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:39:17 by jacha             #+#    #+#             */
/*   Updated: 2025/05/16 07:39:19 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
private:
	AMateria *_templates[4];

public:
	MateriaSource();
	MateriaSource(MateriaSource const &other);
	MateriaSource &operator=(MateriaSource const &other);
	virtual ~MateriaSource();

	void learnMateria(AMateria *);
	AMateria *createMateria(std::string const &type);
};

#endif
