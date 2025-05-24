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
