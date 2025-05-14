#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	_type = "WrongCat";
	std::cout << "WrongCat Default constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
	std::cout << "WrongCat Copy constructor called" << std::endl;
	*this = other;
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	std::cout << "WrongCat Copy assignation operator called" << std::endl;
	if (this != &other)
	{
		WrongAnimal::operator=(other);
		this->_type = other._type;
	}
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat Destructor " << std::endl;
}

void	WrongCat::makeSound() const
{
	std::cout << "Meeaoo!!!!" << std::endl;
}