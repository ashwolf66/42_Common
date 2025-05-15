/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:54:24 by jacha             #+#    #+#             */
/*   Updated: 2025/05/14 12:54:26 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	_type = "Dog";
	std::cout << "Dog Default constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout << "Dog Copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout << "Dog Copy assignation operator called" << std::endl;
	if (this != &other)
		Animal::operator=(other);
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog Destructor " << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << "Bark!!!!" << std::endl;
}
