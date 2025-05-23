#include "Serializer.hpp"

Serializer::Serializer()
{
}

Serializer::Serializer(const Serializer &other)
{
	*this = other;
}

Serializer &Serializer::operator=(const Serializer &other)
{
	if (this != &other)
		*this = other;
	return (*this);
}

Serializer::~Serializer()
{
}

unsigned long Serializer::serialize(Data *ptr)
{
	return (reinterpret_cast<unsigned long>(ptr));
}

Data *Serializer::deserialize(unsigned long raw)
{
	return (reinterpret_cast<Data *>(raw));
}