#include "Serializer.hpp"

int main(int ac, char *av[])
{
	Data data;
	Data *val;
	uintptr_t ptr;

	if (ac != 2)
	{
		std::cout << "Input Argument!!!!" << std::endl;
		return (1);
	}
	data.str = av[1];
	std::cout << "prev : " << data.str << std::endl;

	ptr = Serializer::serialize(&data);
	std::cout << "serialize : " << ptr << std::endl;

	val = Serializer::deserialize(ptr);
	std::cout << "deserialize : " << val->str << std::endl;

	return (0);
}