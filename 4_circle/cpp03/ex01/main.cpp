/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:27:30 by jacha             #+#    #+#             */
/*   Updated: 2025/05/09 20:57:49 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int 	main(void)
{
	{
		std::cout << "-------------------------------test ex00-------------------------------" << std::endl;
		ClapTrap human;
		ClapTrap monster("vem");
	
		human.attack("Dummy");
		human.takeDamage(5);
		human.beRepaired(10);
		human.takeDamage(15);
		human.beRepaired(10);
		for (int i = 0; i < 11; i++)
			monster.attack("Dummy");
		std::cout << "-----------------------------------------------------------------------" << std::endl << std::endl;
	}
	{
		std::cout << "-------------------------------test ex01-------------------------------" << std::endl;
		ScavTrap s_human;
		ScavTrap s_monster("vem");
	
		s_human.guardGate();
		s_human.attack("Dummy");
		s_human.takeDamage(5);
		s_human.beRepaired(10);
		s_human.takeDamage(15);
		s_human.beRepaired(10);
		s_monster.guardGate();
		for (int i = 0; i < 11; i++)
			s_monster.attack("Dummy");
		std::cout << "-----------------------------------------------------------------------" << std::endl << std::endl;
	}
	return (0);
}
