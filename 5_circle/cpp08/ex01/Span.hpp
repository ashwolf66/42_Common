/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:31:53 by jacha             #+#    #+#             */
/*   Updated: 2025/06/01 13:33:42 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cstdlib>

class Span
{
private:
	std::vector<int> _data;
	unsigned int _max;

public:
	Span();
	Span(unsigned int N);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();

	void addNumber(int number);
	int shortestSpan() const;
	int longestSpan() const;

	class FullContainer : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
	class SpanFull : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
	class SpanNotFull : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif
