/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:34:46 by jacha             #+#    #+#             */
/*   Updated: 2025/06/01 13:34:47 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	this->_vec = other._vec;
	this->_deq = other._deq;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vec = other._vec;
		this->_deq = other._deq;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::process(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string token = argv[i];
		for (size_t j = 0; j < token.size(); ++j)
			if (!isdigit(token[j]))
				throw std::runtime_error("Error");

		int num = std::atoi(argv[i]);
		if (num < 0)
			throw std::runtime_error("Error");
		_vec.push_back(num);
		_deq.push_back(num);
	}

	std::cout << "Vector Before: ";
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << _vec[i] << " ";
	std::cout << std::endl;

	std::cout << "Deque Before: ";
	for (size_t i = 0; i < _deq.size(); ++i)
		std::cout << _deq[i] << " ";
	std::cout << std::endl;

	long startVec = getTimeInMicroseconds();
	mergeInsertSortVector(_vec);
	long endVec = getTimeInMicroseconds();

	long startDeq = getTimeInMicroseconds();
	mergeInsertSortDeque(_deq);
	long endDeq = getTimeInMicroseconds();

	std::cout << std::endl;
	std::cout << "Vector After: ";
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << _vec[i] << " ";
	std::cout << std::endl;

	std::cout << "Deque After: ";
	for (size_t i = 0; i < _deq.size(); ++i)
		std::cout << _deq[i] << " ";
	std::cout << std::endl;
	
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector : " << (endVec - startVec) << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
			  << " elements with std::deque  : " << (endDeq - startDeq) << " us" << std::endl;
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &vec)
{
	if (vec.size() <= 1)
		return;

	std::vector<std::pair<int, int> > pairs;
	std::vector<int> mainSequence;
	std::vector<int> subSequence;

	size_t i = 0;
	for (; i + 1 < vec.size(); i += 2)
	{
		int a = vec[i], b = vec[i + 1];
		if (a > b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	int leftover = -1;
	if (i < vec.size())
		leftover = vec[i];

	for (size_t j = 0; j < pairs.size(); ++j)
		mainSequence.push_back(pairs[j].second);

	mergeInsertSortVector(mainSequence);

	for (size_t j = 0; j < pairs.size(); ++j)
	{
		int insertValue = pairs[j].first;
		std::vector<int>::iterator pos = std::lower_bound(mainSequence.begin(), mainSequence.end(), insertValue);
		mainSequence.insert(pos, insertValue);
	}

	if (leftover != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(mainSequence.begin(), mainSequence.end(), leftover);
		mainSequence.insert(pos, leftover);
	}

	vec = mainSequence;
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &deq)
{
	if (deq.size() <= 1)
		return;

	std::deque<std::pair<int, int> > pairs;
	std::deque<int> mainSequence;
	std::deque<int> subSequence;

	size_t i = 0;
	for (; i + 1 < deq.size(); i += 2)
	{
		int a = deq[i], b = deq[i + 1];
		if (a > b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	int leftover = -1;
	if (i < deq.size())
		leftover = deq[i];

	for (size_t j = 0; j < pairs.size(); ++j)
		mainSequence.push_back(pairs[j].second);

		mergeInsertSortDeque(mainSequence);

	for (size_t j = 0; j < pairs.size(); ++j)
	{
		int insertValue = pairs[j].first;
		std::deque<int>::iterator pos = std::lower_bound(mainSequence.begin(), mainSequence.end(), insertValue);
		mainSequence.insert(pos, insertValue);
	}

	if (leftover != -1)
	{
		std::deque<int>::iterator pos = std::lower_bound(mainSequence.begin(), mainSequence.end(), leftover);
		mainSequence.insert(pos, leftover);
	}

	deq = mainSequence;
}

long PmergeMe::getTimeInMicroseconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000L + tv.tv_usec;
}
