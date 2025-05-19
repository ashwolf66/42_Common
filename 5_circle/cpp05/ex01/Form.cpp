#include "Form.hpp"

Form::Form() : _name("jacha"), _signed(false), _grade_sign(150), _grade_exe(150)
{
}

Form::Form(const std::string name, const int grade_sign, const int grade_exe) : _name(name), _signed(false), _grade_sign(grade_sign), _grade_exe(grade_exe)
{
}

Form::Form(const Form &other) : _name(other._name), _signed(other._signed), _grade_sign(other._grade_sign), _grade_exe(other._grade_exe)
{
}

Form &Form::operator=(const Form &other)
{
	if (this != &other)
		this->_signed = other._signed;
	return (*this);
}
Form::~Form()
{
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() <= this->_grade_sign)
		this->_signed = true;
	else
	{
		this->_signed = false;
		throw GradeTooLowException();
	}
}

const std::string Form::getName() const
{
	return (this->_name);
}

bool Form::getSigned() const
{
	return (this->_signed);
}

int Form::getGradeSign() const
{
	return (this->_grade_sign);
}

int Form::getGradeExe() const
{
	return (this->_grade_exe);
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Grade Is Too High!!!!");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Grade Is Too Low!!!!");
}

std::ostream &operator<<(std::ostream &out, const Form &form)
{
	out << form.getName() << " Is Signed: " << form.getSigned() << " Grade To Sign: " << form.getGradeSign() << " Grade To Execute: " << form.getGradeExe();
	return (out);
}