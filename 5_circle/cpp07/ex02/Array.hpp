/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:32:46 by jacha             #+#    #+#             */
/*   Updated: 2025/05/24 16:32:48 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <cstdlib>

template <typename T>
class Array
{
private:
	T *_arr;
	unsigned int _size;

public:
	Array();
	Array(unsigned int n);
	Array(const Array &other);
	Array &operator=(const Array &other);
	~Array();

	T &operator[](unsigned int i);
	unsigned int getSize() const;

	class BadIndex : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#include "Array.tpp"

#endif
