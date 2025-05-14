#include "Cat.hpp"

Cat::Cat()
{
	_type = "Cat";
	std::cout << "Cat Default constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout << "Cat Copy constructor called" << std::endl;
	*this = other;
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Cat Copy assignation operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		this->_type = other._type;
	}
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