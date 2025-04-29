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

int	main(int ac, char **av)
{
	std::string	str;
	Harl		harl;

	if (ac != 2)
	{
		std::cout << "Bad Argument" << std::endl;
		return (0);
	}
	str = av[1];
	for (char &c : str)
		c = std::toupper(static_cast<unsigned char>(c));
	harl.complain(str);
	return (0);
}
