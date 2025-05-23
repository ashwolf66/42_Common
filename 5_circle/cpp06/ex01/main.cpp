#include "Serializer.hpp"

int main(int ac, char *av[])
{
	Data prev;
	Data *next;
	unsigned long ptr;

	if (ac != 2)
	{
		std::cout << "argument count is not 2" << std::endl;
		return (1);
	}
	prev.str = av[1];
	std::cout << "prev : " << prev.str << std::endl;

	ptr = Serializer::serialize(&prev);
	std::cout << "ptr : " << ptr << std::endl;

	next = Serializer::deserialize(ptr);
	std::cout << "next : " << next->str << std::endl;

	return (0);
}