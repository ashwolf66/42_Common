/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:03:32 by jacha             #+#    #+#             */
/*   Updated: 2025/04/28 15:03:34 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

int	main(int ac, char **av)
{
	std::string		ogfilename;
	std::string		cpfilename;

	if (ac != 4)
	{
		std::cout << "Wrong Argument Count!!" << std::endl;
		return (0);
	}
	ogfilename = av[1];
	cpfilename = ogfilename + ".replace";
	std::ifstream ogfile(ogfilename, std::ios::binary);
	if (!ogfile.is_open())
	{
		std::cout << "Open Faile" << std::endl;
		return (0);
	}
	std::ofstream cpfile(ogfilename, std::ios::binary);
	if (!cpfile.is_open())
	{
		std::cout << "Open Faile" << std::endl;
		return (0);
	}
	ogfile.close();
	cpfile.close();
	return (0);
}
