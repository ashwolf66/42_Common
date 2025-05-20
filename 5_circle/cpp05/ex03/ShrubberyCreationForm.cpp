/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:13:14 by jacha             #+#    #+#             */
/*   Updated: 2025/05/20 08:13:16 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyForm", 145, 137), _target("jacha")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("ShrubberyForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other), _target(other._target)
{
	*this = other;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
		_target = other._target;
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (!isSigned())
		throw AForm::NotSigned();
	if (executor.getGrade() > getGradeExe())
		throw AForm::GradeTooLowException();

	std::ofstream ofs((_target + "_shrubbery").c_str());
	if (!ofs.is_open())
	{
		std::cout << "Open Faile" << std::endl;
		ofs.close();
		return;
	}
	ofs << "          **\n"
		<< "         ****\n"
		<< "        ******\n"
		<< "       ********\n"
		<< "      **********\n"
		<< "     ************\n"
		<< "         ||||\n"
		<< "         ||||\n";
	ofs.close();
}
