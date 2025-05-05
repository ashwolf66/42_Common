/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:03:32 by jacha             #+#    #+#             */
/*   Updated: 2025/05/04 17:26:08 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

int	main(int ac, char **av)
{
	std::string	ogfilename;
	std::string	cpfilename;
	std::string	ogline;
	std::string	rpline;
	std::string	tmline;

	if (ac != 4)
	{
		std::cout << "Wrong Argument Count!!" << std::endl;
		return (0);
	}
	ogfilename = av[1];
	ogline = av[2];
	rpline = av[3];
	cpfilename = ogfilename + ".replace";
	std::ifstream ogfile(ogfilename.c_str());
	if (ogline.empty())
	{
		std::cout << "Bad Argument" << std::endl;
		return (0);
	}
	if (!ogfile.is_open())
	{
		std::cout << "Open Faile" << std::endl;
		return (0);
	}
	std::ofstream cpfile(cpfilename.c_str());
	if (!cpfile.is_open())
	{
		std::cout << "Open Faile" << std::endl;
		ogfile.close();
		return (0);
	}
	while (std::getline(ogfile, tmline, '\0'))
	{
		size_t	pos;
		pos = 0;
		while ((pos = tmline.find(ogline, pos)) != std::string::npos)
		{
			tmline.erase(pos, ogline.length());
			tmline.insert(pos, rpline);
			pos += rpline.length();
		}
		cpfile << tmline;
	}
	ogfile.close();
	cpfile.close();
	return (0);
}
