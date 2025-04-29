/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:52:56 by jacha             #+#    #+#             */
/*   Updated: 2025/04/29 16:52:58 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl()
{
}

Harl::~Harl()
{
}

void Harl::debug(void)
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger." << std::endl;
	std::cout << "I really do!" << std::endl;
}

void Harl::info(void)
{
	std::cout << "I cannot believe adding extra bacon costs more money." << std::endl;
	std::cout << "You didn't put enough bacon in my burger!" << std::endl;
	std::cout << "If you did, I wouldn't be asking for more!" << std::endl;
}
void Harl::warning(void)
{
	std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
	std::cout << "I've been coming for years whereas you started working here since last month." << std::endl;
}
void Harl::error(void)
{
	std::cout << "This is unacceptable!" << std::endl;
	std::cout << "I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level)
{
	int i;
	std::string level_arr[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	i = 0;
	while (i < 4)
	{
		if (level == level_arr[i])
			break;
		i++;
	}
	switch (i)
	{
	case 0:
		std::cout << "[ DEBUG ]" << std::endl;
		Harl::debug();
		std::cout << std::endl;
		std::cout << "[ INFO ]" << std::endl;
		Harl::info();
		std::cout << std::endl;
		std::cout << "[ WARNING ]" << std::endl;
		Harl::warning();
		std::cout << std::endl;
		std::cout << "[ ERROR ]" << std::endl;
		Harl::error();
		break;
	case 1:
		std::cout << "[ INFO ]" << std::endl;
		Harl::info();
		std::cout << std::endl;
		std::cout << "[ WARNING ]" << std::endl;
		Harl::warning();
		std::cout << std::endl;
		std::cout << "[ ERROR ]" << std::endl;
		Harl::error();
		break;
	case 2:
		std::cout << "[ WARNING ]" << std::endl;
		Harl::warning();
		std::cout << std::endl;
		std::cout << "[ ERROR ]" << std::endl;
		Harl::error();
		break;
	case 3:
		std::cout << "[ ERROR ]" << std::endl;
		Harl::error();
		break;
	default:
		std::cout << "[ INVALID ]" << std::endl;
		std::cout << "Invalid String!!" << std::endl;
		break;
	}
}