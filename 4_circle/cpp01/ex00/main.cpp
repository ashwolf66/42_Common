/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:51:47 by jacha             #+#    #+#             */
/*   Updated: 2025/04/26 14:51:49 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	std::string	str;
	Zombie *newZombiestatic;

	std::getline(std::cin, str);
	newZombiestatic = newZombie(str);
	newZombiestatic->announce();
	std::getline(std::cin, str);
	randomChump(str);
	delete newZombiestatic;
	return (0);
}
