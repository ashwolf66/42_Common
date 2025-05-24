#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T>
void iter(T *array, int length, void (*func)(T const &))
{
	for (int i = 0; i < length; ++i)
	{
		func(array[i]);
	}
}

template <typename T>
void printElement(T const &elem)
{
	std::cout << elem << std::endl;
}

#endif
