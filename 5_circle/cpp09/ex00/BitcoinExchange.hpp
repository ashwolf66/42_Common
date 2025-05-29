#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <limits>

class BitcoinExchange
{
private:
	std::map<std::string, float> _data;

public:
	BitcoinExchange();
	BitcoinExchange(const std::string &filename);
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();
	void loadDatabase(const std::string &filename);
	float getRate(const std::string &date) const;
	static bool isValidDate(const std::string &date);
	static bool isValidValue(const std::string &valueStr, float &value);
};

#endif
