#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const std::string &filename)
{
	loadDatabase(filename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	this->_data = other._data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		this->_data = other._data;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string date, valueStr;

		if (!std::getline(ss, date, ',') || !std::getline(ss, valueStr))
			continue;

		float value = std::atof(valueStr.c_str());
		_data[date] = value;
	}
}

float BitcoinExchange::getRate(const std::string &date) const
{
	std::map<std::string, float>::const_iterator it = _data.lower_bound(date);
	if (_data.empty())
		throw std::runtime_error("Error: database is empty");
	if (it != _data.end() && it->first == date)
		return it->second;
	if (it != _data.begin())
		--it;
	return it->second;
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	int y, m, d;
	char dash1, dash2;
	std::istringstream ss(date);
	if (!(ss >> y >> dash1 >> m >> dash2 >> d))
		return false;
	if (dash1 != '-' || dash2 != '-')
		return false;
	if (m < 1 || m > 12 || d < 1 || d > 31)
		return false;

	return true;
}

bool BitcoinExchange::isValidValue(const std::string &valueStr, float &value)
{
	std::istringstream ss(valueStr);
	if (!(ss >> value) || !ss.eof())
		return false;
	if (value < 0)
		return false;
	if (value > 1000)
		return false;
	return true;
}