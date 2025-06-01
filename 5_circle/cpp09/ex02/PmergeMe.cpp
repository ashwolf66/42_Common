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
	std::vector<int> mainSequence; // 큰 값들
	std::vector<int> subSequence;  // 작은 값들

	// 1. 짝(pair) 나누기
	size_t i = 0;
	for (; i + 1 < vec.size(); i += 2)
	{
		int a = vec[i], b = vec[i + 1];
		if (a > b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	// 2. 홀수 개일 경우 마지막 하나 따로 저장
	int leftover = -1;
	if (i < vec.size())
		leftover = vec[i];

	// 3. 큰 값으로 메인 시퀀스 구성
	for (size_t j = 0; j < pairs.size(); ++j)
		mainSequence.push_back(pairs[j].second);

	// 4. 메인 시퀀스 정렬 (재귀적으로 자신 호출)
	mergeInsertSortVector(mainSequence);

	// 5. 작은 값들 이진 삽입
	for (size_t j = 0; j < pairs.size(); ++j)
	{
		int insertValue = pairs[j].first;
		std::vector<int>::iterator pos = std::lower_bound(mainSequence.begin(), mainSequence.end(), insertValue);
		mainSequence.insert(pos, insertValue);
	}

	// 6. 남은 홀수 개 수 삽입
	if (leftover != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(mainSequence.begin(), mainSequence.end(), leftover);
		mainSequence.insert(pos, leftover);
	}

	// 7. 최종 결과를 원래 vec에 복사
	vec = mainSequence;
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &deq)
{
	if (deq.size() <= 1)
		return;

	std::deque<std::pair<int, int> > pairs;
	std::deque<int> mainSequence; // 큰 값들
	std::deque<int> subSequence;  // 작은 값들

	// 1. 쌍(pair) 만들기
	size_t i = 0;
	for (; i + 1 < deq.size(); i += 2)
	{
		int a = deq[i], b = deq[i + 1];
		if (a > b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	// 2. 홀수 개라면 마지막 원소 따로 저장
	int leftover = -1;
	if (i < deq.size())
		leftover = deq[i];

	// 3. 큰 값만 추출해서 메인 시퀀스 구성
	for (size_t j = 0; j < pairs.size(); ++j)
		mainSequence.push_back(pairs[j].second);

	// 4. 메인 시퀀스를 재귀적으로 정렬
	mergeInsertSortDeque(mainSequence);

	// 5. 작은 값들을 이진 삽입
	for (size_t j = 0; j < pairs.size(); ++j)
	{
		int insertValue = pairs[j].first;
		std::deque<int>::iterator pos = std::lower_bound(mainSequence.begin(), mainSequence.end(), insertValue);
		mainSequence.insert(pos, insertValue);
	}

	// 6. 남은 홀수 값도 삽입
	if (leftover != -1)
	{
		std::deque<int>::iterator pos = std::lower_bound(mainSequence.begin(), mainSequence.end(), leftover);
		mainSequence.insert(pos, leftover);
	}

	// 7. 결과를 원본 deq에 복사
	deq = mainSequence;
}

long PmergeMe::getTimeInMicroseconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000L + tv.tv_usec;
}
