# ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal
{
private:
	Brain* _brain;
public:
	Dog();
	Dog(const Dog& other);
	Dog& operator=(const Dog& other);
	virtual ~Dog();

	void makeSound() const;
	std::string	getter(int index) const;
	void	setter(int index, const std::string& idea);
};

# endif