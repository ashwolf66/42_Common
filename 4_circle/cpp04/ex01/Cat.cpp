#include "Cat.hpp"

Cat::Cat()
{
	this->_type = "Cat";
	this->_brain = new Brain();
	std::cout << "Cat Default constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout << "Cat Copy constructor called" << std::endl;
	this->_brain = new Brain(*other._brain);
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Cat Copy assignation operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		this->_brain = new Brain(*other._brain);
		this->_type = other._type;
	}
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat Destructor " << std::endl;
	delete this->_brain;
}

void	Cat::makeSound() const
{
	std::cout << "Meeaoo!!!!" << std::endl;
}

std::string	Cat::getter(int index) const
{
	return (_brain->getter(index));
}

void	Cat::setter(int index, const std::string& idea)
{
	_brain->setter(index, idea);
}