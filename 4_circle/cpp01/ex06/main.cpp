/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:53:05 by jacha             #+#    #+#             */
/*   Updated: 2025/04/29 16:53:06 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int ac, char **av)
{
	std::string	str;
	Harl		harl;

	if (ac != 2)
	{
		std::cout << "Bad Argument" << std::endl;
		return (0);
	}
	str = av[1];
	for (size_t i = 0; i < str.length(); i++)
		str[i] = std::toupper(static_cast<unsigned char>(str[i]));
	harl.complain(str);
	return (0);
}
