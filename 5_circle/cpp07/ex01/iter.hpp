/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:32:41 by jacha             #+#    #+#             */
/*   Updated: 2025/05/24 16:32:44 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T>
void iter(T *array, int length, void (*func)(T const &))
{
	if (array == NULL || func == NULL)
		return;
	for (int i = 0; i < length; ++i)
		func(array[i]);
}

template <typename T>
void printElement(T const &arg)
{
	std::cout << arg << std::endl;
}

void toupperString(std::string const &str)
{
	std::string temp = str;
	for (size_t i = 0; i < temp.length(); ++i)
		temp[i] = std::toupper(temp[i]);
	std::cout << temp << std::endl;
}

#endif
