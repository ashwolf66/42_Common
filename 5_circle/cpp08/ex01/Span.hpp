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
	void addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);

	class FullContainer : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif
