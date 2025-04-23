/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:59:41 by jacha             #+#    #+#             */
/*   Updated: 2025/04/23 16:59:46 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char **argv)
{
	std::string	Str;

	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	else if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			std::string temp = argv[i];
			for (int j = 0; j < temp.size(); j++)
			{
				std::cout << (char)toupper(temp[j]);
			}
		}	
		std::cout << std::endl;
	}
	return (0);
}
