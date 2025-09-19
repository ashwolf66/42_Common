#include "vect2.hpp"

vect2::vect2() : _vector{0, 0}
{
}

vect2::vect2(int num1, int num2) : _vector{num1, num2}
{
}

vect2::vect2(const vect2 &other) : _vector(other._vector)
{
}

vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other)
		_vector = other._vector;
	return (*this);
}

vect2::~vect2()
{
}

vect2 vect2::operator+(int num) const
{
	return vect2(_vector[0] + num, _vector[1] + num);
}

vect2 vect2::operator+(const vect2 &other) const
{
	return vect2(_vector[0] + other._vector[0], _vector[1] + other._vector[1]);
}
vect2 vect2::operator-(int num) const
{
	return vect2(_vector[0] - num, _vector[1] - num);
}
vect2 vect2::operator-(const vect2 &other) const
{
	return vect2(_vector[0] - other._vector[0], _vector[1] - other._vector[1]);
}
vect2 vect2::operator*(int num) const
{
	return vect2(_vector[0] * num, _vector[1] * num);
}
vect2 vect2::operator*(const vect2 &other) const
{
	return vect2(_vector[0] * other._vector[0], _vector[1] * other._vector[1]);
}

vect2 &vect2::operator++()
{
	++_vector[0];
	++_vector[1];
	return (*this);
}

vect2 vect2::operator++(int)
{
	vect2 result = *this;
	++_vector[0];
	++_vector[1];
	return (result);
}

vect2 &vect2::operator--()
{
	--_vector[0];
	--_vector[1];
	return (*this);
}

vect2 vect2::operator--(int)
{
	vect2 result = *this;
	--_vector[0];
	--_vector[1];
	return (result);
}

vect2 &vect2::operator+=(int num)
{
	_vector[0] += num;
	_vector[1] += num;
	return (*this);
}

vect2 &vect2::operator+=(const vect2 &other)
{
	_vector[0] += other._vector[0];
	_vector[1] += other._vector[1];
	return (*this);
}

vect2 &vect2::operator-=(int num)
{
	_vector[0] -= num;
	_vector[1] -= num;
	return (*this);
}

vect2 &vect2::operator-=(const vect2 &other)
{
	_vector[0] -= other._vector[0];
	_vector[1] -= other._vector[1];
	return (*this);
}

vect2 &vect2::operator*=(int num)
{
	_vector[0] *= num;
	_vector[1] *= num;
	return (*this);
}

vect2 &vect2::operator*=(const vect2 &other)
{
	_vector[0] *= other._vector[0];
	_vector[1] *= other._vector[1];
	return (*this);
}

bool vect2::operator==(const vect2 &other) const
{
	return (_vector[0] == other._vector[0] && _vector[1] == other._vector[1]);
}

bool vect2::operator!=(const vect2 &other) const
{
	return !(*this == other);
}

vect2 operator*(int num, const vect2 &v)
{
	return vect2(v._vector[0] * num, v._vector[1] * num);
}

std::ostream &operator<<(std::ostream &out, const vect2 &v)
{
	out << "{" << v._vector[0] << ", " << v._vector[1] << "}";
	return (out);
}

int &vect2::operator[](size_t idx)
{
	return _vector[idx];
}

const int &vect2::operator[](size_t idx) const
{
	return _vector[idx];
}

vect2 vect2::operator-() const
{
	return vect2(-_vector[0], -_vector[1]);
}