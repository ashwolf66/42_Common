/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:25:15 by jacha             #+#    #+#             */
/*   Updated: 2025/05/19 09:25:20 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat a("Alice", 2);
		std::cout << a << std::endl;

		a.increment();
		std::cout << a << std::endl;

		a.increment();
		std::cout << a << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "-----" << std::endl;

	try
	{
		Bureaucrat b("Bob", 149);
		std::cout << b << std::endl;

		b.decrement();
		std::cout << b << std::endl;

		b.decrement();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
