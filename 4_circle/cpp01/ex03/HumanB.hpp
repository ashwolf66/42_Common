/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:11:13 by jacha             #+#    #+#             */
/*   Updated: 2025/04/28 10:11:17 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef HUMANB_HPP
#  define HUMANB_HPP

# include "Weapon.hpp"

class HumanB
{
private:
	std::string _name;
	Weapon *_weapon;
public:
	HumanB(std::string name);
	~HumanB();

	void	attack();
	void	setWeapon(Weapon &weapon);
};

# endif