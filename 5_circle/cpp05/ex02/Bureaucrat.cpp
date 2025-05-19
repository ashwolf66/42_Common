/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:49:30 by jacha             #+#    #+#             */
/*   Updated: 2025/05/19 09:25:11 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("jacha"), _grade(150)
{
}

Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name)
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	else
		_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade)
{
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other)
		this->_grade = other._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
}

const std::string Bureaucrat::getName() const
{
	return (this->_name);
}

int Bureaucrat::getGrade() const
{
	return (this->_grade);
}

void Bureaucrat::increment()
{
	if (this->_grade == 1)
		throw GradeTooHighException();
	else
		this->_grade--;
}
void Bureaucrat::decrement()
{
	if (this->_grade == 150)
		throw GradeTooLowException();
	else
		this->_grade++;
}

void Bureaucrat::signForm(AForm &aform)
{
	try
	{
		aform.beSigned(*this);
		std::cout << this->_name << " signed " << aform.getName() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << this->_name << " couldn’t sign " << aform.getName() << " because " << e.what() << std::endl;
	}
}

void Bureaucrat::executeForm(const AForm &aform) const
{
	try
	{
		aform.execute(*this);
		std::cout << _name << " executed " << aform.getName() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << _name << " couldn’t execute " << aform.getName() << " because " << e.what() << std::endl;
	}
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade Is Too High!!!!");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade Is Too Low!!!!");
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade();
	return (out);
}
