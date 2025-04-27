/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:33:54 by jacha             #+#    #+#             */
/*   Updated: 2025/04/27 16:33:56 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(void)
{
	std::string	str = "HI THIS IS BRAIN";
	std::string	*stringPTR = &str;
	std::string	&stringREF = str;

	std::cout << "Address String : " << &str << std::endl;
	std::cout << "Address StringPTR : " << stringPTR << std::endl;
	std::cout << "Address StringREF : " << &stringREF << std::endl;
	std::cout << "Value String : " << str << std::endl;
	std::cout << "Value StringPTR : " << *stringPTR << std::endl;
	std::cout << "Value StringREF : " << stringREF << std::endl;
	return (0);
}
