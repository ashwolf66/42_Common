#include "vec2.hpp"

vec2::vec2() : _vector{0, 0}
{
}

vec2::vec2(int num1, int num2) : _vector{num1, num2}
{
}

vec2::vec2(const vec2 &other) : _vector(other._vector)
{
}

vec2 &vec2::operator=(const vec2 &other)
{
	if (this != &other)
		_vector = other._vector;
	return (*this);
}

vec2::~vec2()
{
}

vec2 vec2::operator+(int num) const
{
	return vec2(_vector[0] + num, _vector[1] + num);
}

vec2 vec2::operator+(const vec2 &other) const
{
	return vec2(_vector[0] + other._vector[0], _vector[1] + other._vector[1]);
}
vec2 vec2::operator-(int num) const
{
	return vec2(_vector[0] - num, _vector[1] - num);
}
vec2 vec2::operator-(const vec2 &other) const
{
	return vec2(_vector[0] - other._vector[0], _vector[1] - other._vector[1]);
}
vec2 vec2::operator*(int num) const
{
	return vec2(_vector[0] * num, _vector[1] * num);
}
vec2 vec2::operator*(const vec2 &other) const
{
	return vec2(_vector[0] * other._vector[0], _vector[1] * other._vector[1]);
}

vec2 &vec2::operator++()
{
	++_vector[0];
	++_vector[1];
	return (*this);
}

vec2 vec2::operator++(int)
{
	vec2 result = *this;
	++_vector[0];
	++_vector[1];
	return (result);
}

vec2 &vec2::operator--()
{
	--_vector[0];
	--_vector[1];
	return (*this);	
}

vec2 vec2::operator--(int)
{
	vec2 result = *this;
	--_vector[0];
	--_vector[1];
	return (result);
}

vec2 &vec2::operator+=(int num)
{
	_vector[0] += num;
	_vector[1] += num;
	return (*this);
}

vec2 &vec2::operator+=(const vec2 &other)
{
	_vector[0] += other._vector[0];
	_vector[1] += other._vector[1];
	return (*this);
}

vec2 &vec2::operator-=(int num)
{
	_vector[0] -= num;
	_vector[1] -= num;
	return (*this);
}

vec2 &vec2::operator-=(const vec2 &other)
{
	_vector[0] -= other._vector[0];
	_vector[1] -= other._vector[1];
	return (*this);
}

vec2 &vec2::operator*=(int num)
{
	_vector[0] *= num;
	_vector[1] *= num;
	return (*this);
}

vec2 &vec2::operator*=(const vec2 &other)
{
	_vector[0] *= other._vector[0];
	_vector[1] *= other._vector[1];
	return (*this);
}

bool vec2::operator==(const vec2 &other) const
{
	return (_vector[0] == other._vector[0] && _vector[1] == other._vector[1]);
}

bool vec2::operator!=(const vec2 &other) const
{
	return !(*this == other);
}

vec2 operator*(int num, const vec2 &v)
{
	return vec2(v._vector[0] * num, v._vector[1] * num);
}

std::ostream &operator<<(std::ostream &out, const vec2 &v)
{
	out << "(" << v._vector[0] << ", " << v._vector[1] << ")";
	return (out);
}