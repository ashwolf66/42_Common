#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	{
		std::cout << "\n[TEST] Invalid form creation\n";
		try
		{
			Form invalidForm("Invalid", 0, 151);
		}
		catch (std::exception &e)
		{
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}
	{
		std::cout << "\n[TEST] Signing process\n";

		Bureaucrat lowRank("Tim", 140);
		Bureaucrat highRank("Susan", 30);

		Form taxForm("TaxForm", 50, 20);
		std::cout << taxForm << std::endl;

		lowRank.signForm(taxForm);
		highRank.signForm(taxForm);
		std::cout << taxForm << std::endl;

		std::cout << "\n[TEST] Signing already signed form\n";
		highRank.signForm(taxForm);
	}
	{
		std::cout << "\n[TEST] Multiple forms and bureaucrats\n";

		Bureaucrat bob("Bob", 100);
		Bureaucrat alice("Alice", 1);

		Form f1("Form-A", 100, 100);
		Form f2("Form-B", 50, 50);
		Form f3("Form-C", 1, 1);

		Form forms[] = {f1, f2, f3};
		Bureaucrat people[] = {bob, alice};

		for (int i = 0; i < 3; ++i)
		{
			std::cout << "\n>> Trying to sign " << forms[i].getName() << std::endl;
			for (int j = 0; j < 2; ++j)
			{
				people[j].signForm(forms[i]);
			}
		}
	}
	std::cout << "\n";
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
	}
	return 0;
}
