/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:39:03 by jacha             #+#    #+#             */
/*   Updated: 2025/05/16 07:39:04 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria
{
public:
	Cure();
	Cure(const Cure &other);
	Cure &operator=(const Cure &other);
	virtual ~Cure();

	virtual AMateria *clone() const;
	virtual void use(ICharacter &target);
};

#endif
