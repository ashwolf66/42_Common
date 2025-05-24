/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:34:47 by jacha             #+#    #+#             */
/*   Updated: 2025/05/24 16:33:16 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

# include <iostream>
# include <iomanip>
# include <exception>
# include <cstdlib>
# include <limits>
# include <cmath>

class ScalarConverter
{
private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter &other);
	ScalarConverter &operator=(const ScalarConverter &other);
	~ScalarConverter();

	static bool isChar(const std::string &literal);
	static bool isInt(const std::string &literal);
	static bool isFloat(const std::string &literal);
	static bool isDouble(const std::string &literal);
	static void printChar(double result);
	static void printInt(double result);
	static void printFloat(double result);
	static void printDouble(double result);

public:
	static void convert(const std::string &literal);
	class Invalid : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif
