/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:43 by jacha             #+#    #+#             */
/*   Updated: 2025/05/24 16:31:45 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>
#include <vector>
#include <iostream>
#include <list>

class NotFoundException : public std::exception
{
public:
	const char *what() const throw()
	{
		return "Value not found in container.";
	}
};

#include "easyfind.tpp"

#endif
