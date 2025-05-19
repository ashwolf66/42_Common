/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:12:49 by jacha             #+#    #+#             */
/*   Updated: 2025/05/20 08:12:51 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
private:
	const std::string _name;
	bool _signed;
	const int _grade_sign;
	const int _grade_exe;

public:
	AForm();
	AForm(const std::string name, const int grade_sign, const int grade_exe);
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);
	virtual ~AForm();

	void beSigned(const Bureaucrat &bureaucrat);
	const std::string getName() const;
	bool getSigned() const;
	int getGradeSign() const;
	int getGradeExe() const;
	bool isSigned() const;
	virtual void execute(const Bureaucrat &executor) const = 0;

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
	class NotSigned : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &out, const AForm &AForm);

#endif
