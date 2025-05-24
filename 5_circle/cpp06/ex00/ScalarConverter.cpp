/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:34:39 by jacha             #+#    #+#             */
/*   Updated: 2025/05/24 16:33:14 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	*this = other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return (*this);
}

ScalarConverter::~ScalarConverter()
{
}

void ScalarConverter::convert(const std::string &literal)
{
	double result;
	try
	{
		if (ScalarConverter::isChar(literal))
			result = static_cast<double>(literal[0]);
		else if (ScalarConverter::isInt(literal))
			result = static_cast<double>(std::strtol(literal.c_str(), NULL, 10));
		else if (ScalarConverter::isFloat(literal))
			result = static_cast<double>(std::strtof(literal.c_str(), NULL));
		else if (ScalarConverter::isDouble(literal))
			result = std::strtod(literal.c_str(), NULL);
		else
			throw ScalarConverter::Invalid();
		printChar(result);
		printInt(result);
		printFloat(result);
		printDouble(result);
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

const char *ScalarConverter::Invalid::what() const throw()
{
	return ("Invalide Argument!!!!");
}

bool ScalarConverter::isChar(const std::string &literal)
{
	if (literal.length() == 1 && !std::isdigit(literal[0]))
		return (true);
	else
		return (false);
}

bool ScalarConverter::isInt(const std::string &literal)
{
	char *e;
	e = NULL;
	std::strtol(literal.c_str(), &e, 10);
	if (*e == '\0')
		return (true);
	else
		return (false);
}

bool ScalarConverter::isFloat(const std::string &literal)
{
	char *e;
	e = NULL;
	std::strtof(literal.c_str(), &e);
	if (*e == 'f' && *(e + 1) == '\0')
		return (true);
	else
		return (false);
}

bool ScalarConverter::isDouble(const std::string &literal)
{
	char *e;
	e = NULL;
	std::strtof(literal.c_str(), &e);
	if (*e == '\0')
		return (true);
	else
		return (false);
}

void ScalarConverter::printChar(double result)
{
	std::cout << "char: ";
	if (std::isnan(result) || result < 0 || result > 127)
		std::cout << "impossible" << std::endl;
	else if (!std::isprint(static_cast<char>(result)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(result) << "'" << std::endl;
}

void ScalarConverter::printInt(double result)
{
	std::cout << "int: ";
	if (std::isnan(result) || result < std::numeric_limits<int>::min() || result > std::numeric_limits<int>::max())
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(result) << std::endl;
}

void ScalarConverter::printFloat(double result)
{
	float f = static_cast<float>(result);
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << f << "f" << std::endl;
}

void ScalarConverter::printDouble(double result)
{
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "double: " << result << std::endl;
}
