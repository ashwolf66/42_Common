#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	Bureaucrat john("John", 1);

	ShrubberyCreationForm shrub("home");
	RobotomyRequestForm robo("Bender");
	PresidentialPardonForm pardon("Ford");

	john.signForm(shrub);
	john.signForm(robo);
	john.signForm(pardon);

	john.executeForm(shrub);
	john.executeForm(robo);
	john.executeForm(pardon);

	return (0);
}
