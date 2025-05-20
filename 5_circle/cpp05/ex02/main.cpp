/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:13:45 by jacha             #+#    #+#             */
/*   Updated: 2025/05/20 08:13:48 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	std::srand(std::time(NULL));
	Bureaucrat john("John", 1);

	ShrubberyCreationForm shrub("home");
	RobotomyRequestForm robo("Bender");
	PresidentialPardonForm pardon("Ford");

	john.signForm(shrub);
	john.signForm(robo);
	john.signForm(pardon);

	std::cout << "\n";

	john.executeForm(shrub);
	std::cout << "\n";
	john.executeForm(robo);
	std::cout << "\n";
	john.executeForm(pardon);

	return (0);
}
