#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
private:
	const std::string _name;
	bool _signed;
	const int _grade_sign;
	const int _grade_exe;

public:
	Form();
	Form(const std::string name, const int grade_sign, const int grade_exe);
	Form(const Form &other);
	Form &operator=(const Form &other);
	~Form();

	void beSigned(const Bureaucrat &bureaucrat);
	const std::string getName() const;
	bool getSigned() const;
	int getGradeSign() const;
	int getGradeExe() const;

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
};

std::ostream &operator<<(std::ostream &out, const Form &form);

#endif