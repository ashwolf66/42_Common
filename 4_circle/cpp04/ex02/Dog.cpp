/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:54:47 by jacha             #+#    #+#             */
/*   Updated: 2025/05/14 12:54:49 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
	this->_type = "Dog";
	this->_brain = new Brain();
	std::cout << "Dog Default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
	std::cout << "Dog Copy constructor called" << std::endl;
	this->_brain = new Brain(*other._brain);
}

Dog &Dog::operator=(const Dog &other)
{
	std::cout << "Dog Copy assignation operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		this->_brain = new Brain(*other._brain);
	}
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog Destructor " << std::endl;
	delete this->_brain;
}

void Dog::makeSound() const
{
	std::cout << "Bark!!!!" << std::endl;
}

std::string Dog::getter(int index) const
{
	return (_brain->getter(index));
}

void Dog::setter(int index, const std::string &idea)
{
	_brain->setter(index, idea);
}
