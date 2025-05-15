/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:54:56 by jacha             #+#    #+#             */
/*   Updated: 2025/05/14 12:55:00 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	{
		const int SIZE = 4;
		Animal *animals[SIZE];
		// Animal animal();

		for (int i = 0; i < SIZE / 2; i++)
			animals[i] = new Dog();
		for (int i = SIZE / 2; i < SIZE; i++)
			animals[i] = new Cat();

		for (int i = 0; i < SIZE; i++)
			animals[i]->makeSound();

		for (int i = 0; i < SIZE; i++)
			delete animals[i];
	}
	std::cout << std::endl;
	{
		Dog dog1;
		dog1.setter(0, "chase the ball");
		Dog dog2 = dog1;

		std::cout << "Dog1 idea: " << dog1.getter(0) << std::endl;
		std::cout << "Dog2 idea: " << dog2.getter(0) << std::endl;

		dog2.setter(0, "sleep");

		std::cout << "Dog1 idea after change: " << dog1.getter(0) << std::endl;
		std::cout << "Dog2 idea after change: " << dog2.getter(0) << std::endl;
	}
	return (0);
}
