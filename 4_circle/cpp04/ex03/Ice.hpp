/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:39:11 by jacha             #+#    #+#             */
/*   Updated: 2025/05/16 07:39:12 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria
{
public:
	Ice();
	Ice(Ice const &other);
	Ice &operator=(Ice const &other);
	virtual ~Ice();

	virtual AMateria *clone() const;
	virtual void use(ICharacter &target);
};

#endif
