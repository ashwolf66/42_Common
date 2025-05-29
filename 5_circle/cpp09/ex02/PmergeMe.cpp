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

	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << _vec[i] << " ";
	std::cout << std::endl;

	long startVec = getTimeInMicroseconds();
	mergeInsertSortVector(_vec);
	long endVec = getTimeInMicroseconds();

	long startDeq = getTimeInMicroseconds();
	mergeInsertSortDeque(_deq);
	long endDeq = getTimeInMicroseconds();

	std::cout << "After: ";
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << _vec[i] << " ";
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

	size_t mid = vec.size() / 2;
	std::vector<int> left(vec.begin(), vec.begin() + mid);
	std::vector<int> right(vec.begin() + mid, vec.end());

	mergeInsertSortVector(left);
	mergeInsertSortVector(right);

	std::merge(left.begin(), left.end(), right.begin(), right.end(), vec.begin());
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &deq)
{
	if (deq.size() <= 1)
		return;

	size_t mid = deq.size() / 2;
	std::deque<int> left(deq.begin(), deq.begin() + mid);
	std::deque<int> right(deq.begin() + mid, deq.end());

	mergeInsertSortDeque(left);
	mergeInsertSortDeque(right);

	std::merge(left.begin(), left.end(), right.begin(), right.end(), deq.begin());
}

long PmergeMe::getTimeInMicroseconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000L + tv.tv_usec;
}