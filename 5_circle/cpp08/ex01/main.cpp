#include "Span.hpp"

int main()
{
	try
	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest : " << sp.longestSpan() << std::endl;

		Span bigSpan(10000);
		for (int i = 0; i < 10000; ++i)
			bigSpan.addNumber(rand());
		std::cout << "Big Shortest: " << bigSpan.shortestSpan() << std::endl;
		std::cout << "Big Longest : " << bigSpan.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return (0);
}
