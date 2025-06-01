/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:43 by jacha             #+#    #+#             */
/*   Updated: 2025/06/01 13:33:30 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>
#include <vector>
#include <iostream>
#include <list>

template <typename T>
typename T::iterator easyfind(T &container, int value);

class NotFoundException : public std::exception
{
public:
	virtual const char *what() const throw();
};

#include "easyfind.tpp"

#endif
