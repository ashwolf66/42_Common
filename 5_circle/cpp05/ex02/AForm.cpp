#include "AForm.hpp"

AForm::AForm() : _name("jacha"), _signed(false), _grade_sign(150), _grade_exe(150)
{
}

AForm::AForm(const std::string name, const int grade_sign, const int grade_exe) : _name(name), _signed(false), _grade_sign(grade_sign), _grade_exe(grade_exe)
{
	if (this->_grade_sign < 1 || this->_grade_exe < 1)
		throw GradeTooHighException();
	if (this->_grade_sign > 150 || this->_grade_exe > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &other) : _name(other._name), _signed(other._signed), _grade_sign(other._grade_sign), _grade_exe(other._grade_exe)
{
}

AForm &AForm::operator=(const AForm &other)
{
	if (this != &other)
		this->_signed = other._signed;
	return (*this);
}
AForm::~AForm()
{
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() <= this->_grade_sign)
		this->_signed = true;
	else
	{
		this->_signed = false;
		throw GradeTooLowException();
	}
}

const std::string AForm::getName() const
{
	return (this->_name);
}

bool AForm::getSigned() const
{
	return (this->_signed);
}

int AForm::getGradeSign() const
{
	return (this->_grade_sign);
}

int AForm::getGradeExe() const
{
	return (this->_grade_exe);
}

bool AForm::isSigned() const
{
	return (this->_signed);
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Grade Is Too High!!!!");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Grade Is Too Low!!!!");
}

const char *AForm::NotSigned::what() const throw()
{
	return ("Not Signed!!!!");
}

std::ostream &operator<<(std::ostream &out, const AForm &AForm)
{
	out << AForm.getName() << " Is Signed: " << AForm.getSigned() << " Grade To Sign: " << AForm.getGradeSign() << " Grade To Execute: " << AForm.getGradeExe();
	return (out);
}