/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:09:36 by jacha             #+#    #+#             */
/*   Updated: 2025/05/01 15:09:40 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::literal = 8;

Fixed::Fixed() : num(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed::Fixed(const int n)
{
	std::cout << "Int constructor called" << std::endl;
	num = n << literal;
}

Fixed::Fixed(const float n)
{
	std::cout << "Float constructor called" << std::endl;
	num = (int)roundf(n * (1 << literal));
}

Fixed& Fixed::operator=(const Fixed &other)
{
	std::cout << "Copy assignation operator called" << std::endl;
	if (this != &other)
		num = other.getRawBits();
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
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

std::ostream& operator<<(std::ostream& str, const Fixed &other)
{
	str << other.toFloat();
	return (str);
}