/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:34:54 by jacha             #+#    #+#             */
/*   Updated: 2025/04/27 14:37:28 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	std::string	str;
	Zombie		*horde;
	int			N;

	std::cout << "ZombieName : ";
	std::getline(std::cin, str);
	std::cout << "ZombieCount : ";
	std::cin >> N;
	horde = zombieHorde(N, str);
	for (int i = 0; i < N; i++)
	{
		std::cout << "Number " << i + 1 << " : ";
		horde[i].announce();
	}
	delete[] horde;
	return (0);
}
