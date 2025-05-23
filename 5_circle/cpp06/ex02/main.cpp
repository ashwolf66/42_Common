#include "Base.hpp"
#include "Oper.hpp"

int main(void)
{
	srand(time(NULL));
	Base *ptr = generate();
	Base &ref = *ptr;

	identify(ptr);
	identify(ref);

	delete ptr;

	return (0);
}