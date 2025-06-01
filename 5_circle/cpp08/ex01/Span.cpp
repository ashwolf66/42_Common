/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:51 by jacha             #+#    #+#             */
/*   Updated: 2025/06/01 13:33:40 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() : _max(0)
{
}

Span::Span(unsigned int N) : _max(N)
{
}

Span::Span(const Span &other)
{
	this->_data = other._data;
	this->_max = other._max;
}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		this->_data = other._data;
		this->_max = other._max;
	}
	return (*this);
}
Span::~Span()
{
}

void Span::addNumber(int number)
{
	if (_data.size() >= _max)
		throw SpanFull();
	_data.push_back(number);
}

int Span::shortestSpan() const
{
	if (_data.size() < 2)
		throw SpanNotFull();

	size_t i = 1;
	std::vector<int> tmp = _data;
	std::sort(tmp.begin(), tmp.end());

	int minSpan = tmp[i] - tmp[i - 1];
	for (i = 1; i < tmp.size() - 1; ++i)
	{
		int span = tmp[i + 1] - tmp[i];
		if (span < minSpan)
			minSpan = span;
	}
	return minSpan;
}

int Span::longestSpan() const
{
	if (_data.size() < 2)
		throw SpanNotFull();

	std::vector<int> tmp = _data;
	std::sort(tmp.begin(), tmp.end());

	return (tmp[tmp.size() - 1] - tmp[0]);
}

const char *Span::FullContainer::what() const throw()
{
	return ("Container Is Full!!!!");
}

const char *Span::SpanFull::what() const throw()
{
	return ("Span Is Full!!!!");
}

const char *Span::SpanNotFull::what() const throw()
{
	return ("Span Is Not Enough!!!!");
}
