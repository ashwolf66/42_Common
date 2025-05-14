#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain Default constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		this->_ideas[i] = "Brain";
}

Brain::Brain(const Brain& other)
{
	std::cout << "Brain Copy constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		this->_ideas[i] = other._ideas[i] + "_copy";
}

Brain& Brain::operator=(const Brain& other)
{
	std::cout << "Brain Copy assignation operator called" << std::endl;
	if (this != &other)
	{
		for (int i = 0; i < 100; i++)
			this->_ideas[i] = other._ideas[i];
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain Destructor " << std::endl;
}

std::string	Brain::getter(int index) const
{
	if (index >= 0 && index <= 100)
		return (this->_ideas[index]);
	return ("Bad Index");
}

void	Brain::setter(int index, const std::string& idea)
{
	if (index >= 0 && index <= 100)
		this->_ideas[index] = idea;
}