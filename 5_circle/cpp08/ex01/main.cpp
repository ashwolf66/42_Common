/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:55 by jacha             #+#    #+#             */
/*   Updated: 2025/05/24 16:31:57 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main()
{
	try
	{
		int min;
		int max;
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		min = sp.shortestSpan();
		max = sp.longestSpan();
		std::cout << "Shortest: " << min << std::endl;
		std::cout << "Longest : " << max << std::endl;

		Span wrongSpan(1);
		wrongSpan.addNumber(5);
		min = wrongSpan.shortestSpan();
		max = wrongSpan.longestSpan();
		std::cout << "Big Shortest: " << min << std::endl;
		std::cout << "Big Longest : " << max << std::endl;

		//Span wrong = Span(4);
		//wrong.addNumber(6);
		//wrong.addNumber(3);
		//wrong.addNumber(17);
		//wrong.addNumber(9);
		//wrong.addNumber(11);
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return (0);
}
