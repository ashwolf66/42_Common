#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <stdexcept>
#include <sys/time.h>

class PmergeMe
{
private:
	std::vector<int> _vec;
	std::deque<int> _deq;

public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
	void process(int argc, char **argv);
	static void mergeInsertSortVector(std::vector<int> &vec);
	static void mergeInsertSortDeque(std::deque<int> &deq);
	static long getTimeInMicroseconds();
};
#endif
