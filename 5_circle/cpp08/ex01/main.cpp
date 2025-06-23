/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:55 by jacha             #+#    #+#             */
/*   Updated: 2025/06/01 13:33:43 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main()
{
	int min;
	int max;
	try
	{
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
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	try
	{
		Span wrongSpan(1);
		wrongSpan.addNumber(5);
		min = wrongSpan.shortestSpan();
		max = wrongSpan.longestSpan();
		std::cout << "Big Shortest: " << min << std::endl;
		std::cout << "Big Longest : " << max << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	try
	{
		 Span wrong = Span(4);
		 wrong.addNumber(6);
		 wrong.addNumber(3);
		 wrong.addNumber(17);
		 wrong.addNumber(9);
		 wrong.addNumber(11);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	try
	{
		std::vector<int> vec;
		vec.push_back(10);
		vec.push_back(20);
		vec.push_back(30);
		vec.push_back(40);

		Span spRange(10);
		spRange.addNumber(vec.begin(), vec.end());
		std::cout << "multiple addNumber Size : " << std::distance(vec.begin(), vec.end()) << std::endl;

		spRange.addNumber(50);

		min = spRange.shortestSpan();
		max = spRange.longestSpan();
		std::cout << "Range Shortest: " << min << std::endl;
		std::cout << "Range Longest : " << max << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	

	return (0);
}
