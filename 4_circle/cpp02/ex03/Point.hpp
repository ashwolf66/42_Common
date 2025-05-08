/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:58:09 by jacha             #+#    #+#             */
/*   Updated: 2025/05/07 14:58:10 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef POINT_HPP
#  define POINT_HPP

# include <iostream>
# include <cmath>
# include "Fixed.hpp"

class Point
{
private:
	const Fixed _x;
	const Fixed _y;
public:
	Point();
	Point(const float x_val, const float y_val);
	Point(const Point& other);
	Point& operator=(const Point& other);
	~Point();
	const Fixed &getx() const;
	const Fixed &gety() const;
};

# endif
