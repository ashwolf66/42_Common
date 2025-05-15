/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:54:20 by jacha             #+#    #+#             */
/*   Updated: 2025/05/14 12:54:21 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
	_type = "Cat";
	std::cout << "Cat Default constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout << "Cat Copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Cat Copy assignation operator called" << std::endl;
	if (this != &other)
		Animal::operator=(other);
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat Destructor " << std::endl;
}

void	Cat::makeSound() const
{
	std::cout << "Meeaoo!!!!" << std::endl;
}
