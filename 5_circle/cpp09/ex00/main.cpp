#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	std::ifstream infile(argv[1]);
	if (!infile.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	BitcoinExchange btc("data.csv");

	std::string line;
	std::getline(infile, line);

	while (std::getline(infile, line))
	{
		std::string date, valueStr;
		std::stringstream ss(line);

		if (line.empty())
			continue;

		if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		date.erase(date.find_last_not_of(" \t") + 1);
		date.erase(0, date.find_first_not_of(" \t"));
		valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
		valueStr.erase(0, valueStr.find_first_not_of(" \t"));

		if (!BitcoinExchange::isValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		float value;
		if (!BitcoinExchange::isValidValue(valueStr, value))
		{
			if (valueStr.find('-') != std::string::npos)
				std::cerr << "Error: not a positive number." << std::endl;
			else
				std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		float rate = btc.getRate(date);
		std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
	}

	return 0;
}
