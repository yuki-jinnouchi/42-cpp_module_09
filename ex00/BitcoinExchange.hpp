#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

#include "Date.hpp"

class BitcoinExchange {
 public:
  // Orthodox Canonical Form
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange& other);
  BitcoinExchange& operator=(const BitcoinExchange& other);
  ~BitcoinExchange();

  // Member functions
  bool loadDatabase(const std::string& filename);
  void processInputFile(const std::string& filename);

 private:
  // Member variables
  std::map<Date, double> _database;

  // Helper functions
  bool isValidDateRange(const Date& date);
  bool isValidRate(const std::string& rate);
  bool isValidValue(const std::string& value);
  double getExchangeRate(const Date& date);
  void printResult(const std::string& date, double value, double rate);
  void printError(const std::string& message);

  // Utility functions
  int stringToInt(const std::string& str);
  double stringToDouble(const std::string& str);
  std::string doubleToString(double value);
};

#endif
