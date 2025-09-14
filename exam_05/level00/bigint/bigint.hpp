#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class Bigint
{
private:
	std::string value;
public:
	Bigint();
	Bigint(const Bigint& other);
	Bigint& operator=(const Bigint& other);
	~Bigint();
	
	Bigint(unsigned long long num);
	Bigint(const std::string& str);
	
	Bigint operator+(const Bigint& other) const;
	Bigint& operator+=(const Bigint& other);
	Bigint operator<<(size_t shift) const;
	Bigint& operator<<=(size_t shift);
	Bigint operator<<(const Bigint& other) const;
	Bigint& operator<<=(const Bigint& other);
	Bigint operator>>(size_t shift) const;
	Bigint& operator>>=(size_t shift);
	Bigint operator>>(const Bigint& other) const;
	Bigint& operator>>=(const Bigint& other);
	
	bool operator>(const Bigint& other) const;
	bool operator<(const Bigint& other) const;
	bool operator>=(const Bigint& other) const;
	bool operator<=(const Bigint& other) const;
	bool operator==(const Bigint& other) const;
	bool operator!=(const Bigint& other) const;
	
	Bigint& operator++();
	Bigint operator++(int);
	
	friend std::ostream& operator<<(std::ostream& out, const Bigint& result);
};

#endif
