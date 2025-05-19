/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:13:02 by jacha             #+#    #+#             */
/*   Updated: 2025/05/20 08:13:04 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &other)
{
	(void)other;
}

Intern &Intern::operator=(const Intern &other)
{
	(void)other;
	return *this;
}

Intern::~Intern()
{
}

AForm *Intern::makeForm(const std::string &formName, const std::string &target)
{
	int i = 0;
	std::string available_forms[3] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};

	while (i < 3 && formName != available_forms[i])
		i++;

	switch (i)
	{
	case 0:
		std::cout << "Intern creates " << formName << std::endl;
		return (new ShrubberyCreationForm(target));
	case 1:
		std::cout << "Intern creates " << formName << std::endl;
		return (new RobotomyRequestForm(formName));
	case 2:
		std::cout << "Intern creates " << formName << std::endl;
		return (new PresidentialPardonForm(target));
	default:
		std::cout << "Form is not existing" << std::endl;
		return NULL;
	}
}
