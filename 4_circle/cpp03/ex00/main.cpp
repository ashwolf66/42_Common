/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:27:30 by jacha             #+#    #+#             */
/*   Updated: 2025/05/12 15:10:36 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int 	main(void)
{
	{
		ClapTrap human;
		ClapTrap monster("vem");
	
		human.attack("Dummy");
		human.takeDamage(5);
		human.beRepaired(10);
		human.takeDamage(15);
		human.beRepaired(10);
		for (int i = 0; i < 11; i++)
			monster.attack("Dummy");
	}
	return (0);
}
