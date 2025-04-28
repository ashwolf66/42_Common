/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:10:35 by jacha             #+#    #+#             */
/*   Updated: 2025/04/28 10:10:36 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef WEAPON_H
#  define WEAPON_H

# include <iostream>

class Weapon
{
private:
	std::string	_type;
public:
	Weapon();
	Weapon(std::string type);
	~Weapon();
	void				setType(std::string type);
	const std::string	&getType() const;
};

# endif