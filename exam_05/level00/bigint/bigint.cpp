#include "bigint.hpp"
#include <algorithm>

Bigint::Bigint() : value("0")
{
}

Bigint::Bigint(const Bigint &other) : value(other.value)
{
}

Bigint &Bigint::operator=(const Bigint &other)
{
	if (this != &other)
		value = other.value;
	return *this;
}

Bigint::~Bigint()
{
}

Bigint::Bigint(unsigned long long num) : value(std::to_string(num))
{
}

Bigint::Bigint(const std::string &str) : value(str)
{
}

Bigint Bigint::operator+(const Bigint &other) const
{
	std::string result;
	int n1 = value.length() - 1;
	int n2 = other.value.length() - 1;
	int temp = 0;
	int sum = 0;

	while (n1 >= 0 || n2 >= 0 || temp)
	{
		sum = temp;
		if (n1 >= 0)
			sum += value[n1] - '0';
		if (n2 >= 0)
			sum += other.value[n2] - '0';
		result.push_back((sum % 10) + '0');
		temp = sum / 10;
		n1--;
		n2--;
	}
	std::reverse(result.begin(), result.end());
	return (Bigint(result));
}

Bigint &Bigint::operator+=(const Bigint &other)
{
	*this = *this + other;
	return (*this);
}

Bigint Bigint::operator<<(size_t shift) const
{
	std::string result = value;
	result.append(shift, '0');
	return (Bigint(result));
}

Bigint &Bigint::operator<<=(size_t shift)
{
	value.append(shift, '0');
	return (*this);
}

Bigint Bigint::operator<<(const Bigint &other) const
{
	size_t shift = std::stoull(other.value);
	return (*this << shift);
}

Bigint &Bigint::operator<<=(const Bigint &other)
{
	size_t shift = std::stoull(other.value);
	return (*this <<= shift);
}

Bigint Bigint::operator>>(size_t shift) const
{
	std::string result = value;
	result = result.substr(0, result.length() - shift);
	return (Bigint(result));
}

Bigint &Bigint::operator>>=(size_t shift)
{
	value = value.substr(0, value.length() - shift);
	return (*this);
}

Bigint Bigint::operator>>(const Bigint &other) const
{
	size_t shift = std::stoull(other.value);
	return (*this >> shift);
}

Bigint &Bigint::operator>>=(const Bigint &other)
{
	size_t shift = std::stoull(other.value);
	return (*this >>= shift);
}

bool Bigint::operator>(const Bigint &other) const
{
	if (value.length() != other.value.length())
		return (value.length() > other.value.length());
	return (value > other.value);
}

bool Bigint::operator<(const Bigint &other) const
{
	if (value.length() != other.value.length())
		return (value.length() < other.value.length());
	return (value < other.value);
}

bool Bigint::operator>=(const Bigint &other) const
{
	return !(*this < other);
}

bool Bigint::operator<=(const Bigint &other) const
{
	return !(*this > other);
}

bool Bigint::operator==(const Bigint &other) const
{
	return (value == other.value);
}

bool Bigint::operator!=(const Bigint &other) const
{
	return (value != other.value);
}

Bigint &Bigint::operator++()
{
	*this += Bigint(1);
	return (*this);
}

Bigint Bigint::operator++(int)
{
	Bigint temp = *this;
	++(*this);
	return (temp);
}

std::ostream &operator<<(std::ostream &out, const Bigint &result)
{
	out << result.value;
	return (out);
}
