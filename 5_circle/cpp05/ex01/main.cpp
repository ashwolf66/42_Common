#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try
	{
		Bureaucrat alice("Alice", 50);
		Form formA("A-Form", 30, 40);

		std::cout << formA << std::endl;
		alice.signForm(formA);
		Bureaucrat bob("Bob", 20);
		bob.signForm(formA);
		std::cout << formA << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}
