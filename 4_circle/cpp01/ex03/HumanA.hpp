/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:10:54 by jacha             #+#    #+#             */
/*   Updated: 2025/04/28 10:10:55 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef HUMANA_HPP
#  define HUMANA_HPP

# include "Weapon.hpp"

class HumanA
{
private:
	std::string	_name;
	Weapon &_weapon;
public:
	HumanA(std::string name, Weapon &weapon);
	~HumanA();

	void	attack();
};

# endif