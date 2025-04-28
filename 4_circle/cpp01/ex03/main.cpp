/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:10:25 by jacha             #+#    #+#             */
/*   Updated: 2025/04/28 10:20:48 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int	main()
{
	{
		Weapon	club = Weapon("crude spiked club");

		HumanA	bob("Bob", club);
		bob.attack();
		club.setType("some other type of clube");
		bob.attack();
	}
	{
		Weapon	club = Weapon("crude spiked club");

		HumanB	jim("jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of clube");
		jim.attack();
	}
}
