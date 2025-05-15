/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:54:49 by jacha             #+#    #+#             */
/*   Updated: 2025/05/14 12:54:52 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
private:
	Brain *_brain;

public:
	Dog();
	Dog(const Dog &other);
	Dog &operator=(const Dog &other);
	virtual ~Dog();

	void makeSound() const;
	std::string getter(int index) const;
	void setter(int index, const std::string &idea);
};

#endif
