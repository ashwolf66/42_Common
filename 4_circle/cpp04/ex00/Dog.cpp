#include "Dog.hpp"

Dog::Dog()
{
	_type = "Dog";
	std::cout << "Dog Default constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout << "Dog Copy constructor called" << std::endl;
	*this = other;
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout << "Dog Copy assignation operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		this->_type = other._type;
	}
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