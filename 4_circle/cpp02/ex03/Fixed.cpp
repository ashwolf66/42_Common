/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:09:36 by jacha             #+#    #+#             */
/*   Updated: 2025/05/07 14:58:00 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::literal = 8;

Fixed::Fixed() : num(0)
{

}

Fixed::Fixed(const Fixed &other)
{
	*this = other;
}

Fixed::Fixed(const int n)
{
	num = n << literal;
}

Fixed::Fixed(const float n)
{
	num = (int)roundf(n * (1 << literal));
}

Fixed& Fixed::operator=(const Fixed &other)
{
	if (this != &other)
		num = other.getRawBits();
	return (*this);
}

Fixed::~Fixed()
{

}

int	Fixed::getRawBits(void) const
{
	return (num);
}

void	Fixed::setRawBits(int const raw)
{
	num = raw;
}

float	Fixed::toFloat(void) const {
	return (float)num / (float)(1 << literal);
}

int	Fixed::toInt(void) const {
	return (int)(num >> literal);
}

bool Fixed::operator>(const Fixed& other) const
{
	return (this->toFloat() > other.toFloat());
}

bool Fixed::operator<(const Fixed& other) const
{
	return (this->toFloat() < other.toFloat());
}

bool Fixed::operator>=(const Fixed& other) const
{
	return (this->toFloat() >= other.toFloat());
}

bool Fixed::operator<=(const Fixed& other) const
{
	return (this->toFloat() <= other.toFloat());
}

bool Fixed::operator==(const Fixed& other) const
{
	return (this->toFloat() == other.toFloat());
}

bool Fixed::operator!=(const Fixed& other) const
{
	return (this->toFloat() != other.toFloat());
}

Fixed Fixed::operator+(const Fixed& other) const
{
	return (this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed& other) const
{
	return (this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed& other) const
{
	return (this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed& other) const
{
	return (this->toFloat() / other.toFloat());
}

Fixed& Fixed::operator++()
{
	this->num++;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	this->num++;
	return (temp);
}

Fixed& Fixed::operator--()
{
	this->num--;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	this->num--;
	return (temp);
}

Fixed& Fixed::min(Fixed& n1, Fixed& n2)
{
	return (n1 < n2 ? n1 : n2);
}

const Fixed& Fixed::min(const Fixed& n1, const Fixed& n2)
{
	return (n1 < n2 ? n1 : n2);
}

Fixed& Fixed::max(Fixed& n1, Fixed& n2)
{
	return (n1 > n2 ? n1 : n2);
}

const Fixed& Fixed::max(const Fixed& n1, const Fixed& n2)
{
	return (n1 > n2 ? n1 : n2);
}

std::ostream& operator<<(std::ostream& str, const Fixed &other)
{
	str << other.toFloat();
	return (str);
}
