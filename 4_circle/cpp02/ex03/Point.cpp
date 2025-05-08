/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:06 by jacha             #+#    #+#             */
/*   Updated: 2025/05/07 14:58:08 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : _x(0), _y(0)
{
	
}

Point::Point(const float x_val, const float y_val) : _x(x_val), _y(y_val)
{

}

Point::Point(const Point& other) : _x(other._x), _y(other._y)
{

}

Point& Point::operator=(const Point& other)
{
	(void)other;
	return (*this);
}

Point::~Point()
{
	
}

const Fixed& Point::getx() const
{
	return (_x);
}

const Fixed& Point::gety() const
{
	return (_y);
}