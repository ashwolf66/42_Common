/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:09:40 by jacha             #+#    #+#             */
/*   Updated: 2025/05/07 14:58:02 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FIXED_HPP
#  define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
private:
	int	num;
	static const int literal;
public:
	Fixed();
	Fixed(const Fixed& other);
	Fixed(const int n);
	Fixed(const float n);
	Fixed& operator = (const Fixed& other);
	~Fixed();
	
	int	getRawBits(void) const;
	void setRawBits(int const raw);
	float toFloat(void) const;
	int toInt(void) const;

	bool operator> (const Fixed& other) const;
	bool operator< (const Fixed& other) const;
	bool operator>= (const Fixed& other) const;
	bool operator<= (const Fixed& other) const;
	bool operator== (const Fixed& other) const;
	bool operator!= (const Fixed& other) const;

	Fixed operator+ (const Fixed& other) const;
	Fixed operator- (const Fixed& other) const;
	Fixed operator* (const Fixed& other) const;
	Fixed operator/ (const Fixed& other) const;

	Fixed& operator++ ();
	Fixed operator++ (int);
	Fixed& operator-- ();
	Fixed operator-- (int);

	static Fixed& min(Fixed& n1, Fixed& n2);
	static const Fixed& min(const Fixed& n1, const Fixed& n2);
	static Fixed& max(Fixed& n1, Fixed& n2);
	static const Fixed& max(const Fixed& n1, const Fixed& n2);
};

std::ostream&	operator<<(std::ostream& str, const Fixed& other);

# endif
