/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:51 by jacha             #+#    #+#             */
/*   Updated: 2025/05/24 16:31:53 by jacha            ###   ########.fr       */
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
	*this = other;
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
		throw std::out_of_range("Span is full");
	_data.push_back(number);
}

int Span::shortestSpan() const
{
	if (_data.size() < 2)
		throw std::logic_error("Not enough elements");

	std::vector<int> tmp = _data;
	std::sort(tmp.begin(), tmp.end());

	int minSpan = std::numeric_limits<int>::max();
	for (size_t i = 0; i < tmp.size() - 1; ++i)
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
		throw std::logic_error("Not enough elements");

	int minVal = *std::min_element(_data.begin(), _data.end());
	int maxVal = *std::max_element(_data.begin(), _data.end());

	return maxVal - minVal;
}

void Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	if (_data.size() + std::distance(begin, end) > _max)
		throw FullContainer();
	_data.insert(_data.end(), begin, end);
}

const char *Span::FullContainer::what() const throw()
{
	return ("Container Is Full!!!!");
}
