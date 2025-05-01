/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:09:05 by jacha             #+#    #+#             */
/*   Updated: 2025/05/01 15:09:06 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FIXED_HPP
#  define FIXED_HPP

# include <iostream>

class Fixed
{
private:
	int	num;
	static const int literal;
public:
	Fixed();
	Fixed(const Fixed& other);
	Fixed& operator = (const Fixed& other);
	~Fixed();
	
	int	getRawBits(void) const;
	void setRawBits(int const raw);
};

# endif
