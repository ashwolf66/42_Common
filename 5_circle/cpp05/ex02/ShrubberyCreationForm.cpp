#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyForm", 145, 137), _target("jacha")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("ShrubberyForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other), _target(other._target)
{
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

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const
{
	if (!isSigned())
		throw AForm::NotSigned();
	if (executor.getGrade() > getGradeExe())
		throw AForm::GradeTooLowException();

	std::ofstream ofs((_target + "_shrubbery").c_str());
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
