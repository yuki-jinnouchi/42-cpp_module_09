#include "BitcoinExchange.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Date.hpp"

// Orthodox Canonical Form
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
  if (this != &other) {
    _database = other._database;
  }
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Member functions
bool BitcoinExchange::loadDatabase(const std::string& filename) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) return false;

  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string str_date;
    double rate;
    if (!std::getline(iss, str_date, ',') || !(iss >> rate)) {
      printError("invalid line format in database: " + line);
      break;
    }
    Date date(str_date);
    if (!date.isValid()) {
      if (!date.isValidFormat()) {
        printError("invalid date format in database: " + str_date);
      } else if (!date.isValidDate()) {
        printError("invalid date in database: " + str_date);
      }
      return false;
    }
    if (!isValidRate(doubleToString(rate))) {
      printError("invalid rate in database: " + doubleToString(rate));
      return false;
    }
    _database[date] = rate;
  }
  file.close();

  if (_database.empty()) return false;
  return true;
}

void BitcoinExchange::processInputFile(const std::string& filename) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    printError("could not open file.");
    return;
  }

  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string str_date, valueStr;
    if (!std::getline(iss, str_date, '|') || !std::getline(iss, valueStr)) {
      printError("bad input => " + line);
      continue;
    }
    str_date.erase(std::remove(str_date.begin(), str_date.end(), ' '),
                   str_date.end());
    valueStr.erase(std::remove(valueStr.begin(), valueStr.end(), ' '),
                   valueStr.end());
    Date date(str_date);
    if (!date.isValid()) {
      if (!date.isValidFormat()) {
        printError("invalid date format => " + str_date);
      } else if (!date.isValidDate()) {
        printError("invalid date => " + str_date);
      }
      continue;
    }
    if (!isValidDateRange(date)) continue;
    if (!isValidValue(valueStr)) continue;
    double value = stringToDouble(valueStr);
    double rate = getExchangeRate(date);
    if (rate < 0)
      printError("No exchange rate found for date => " + str_date);
    else
      printResult(str_date, value, rate * value);
  }
}

// Helper functions
bool BitcoinExchange::isValidDateRange(const Date& date) {
  Date minDate = _database.begin()->first;

  if (date < minDate) {
    printError("date out of Database range: " + date.toString());
    return false;
  }
  return true;
}

bool BitcoinExchange::isValidRate(const std::string& rate) {
  if (rate.empty()) return false;
  if (rate[0] == '-') return false;
  if (rate[0] == '.') return false;
  if (rate[rate.size() - 1] == '.') return false;
  if (rate.find_first_not_of("0123456789.") != std::string::npos) return false;
  if (std::count(rate.begin(), rate.end(), '.') > 1) {
    return false;
  }
  return true;
}

bool BitcoinExchange::isValidValue(const std::string& value) {
  if (value.empty()) return false;
  if (value.find_first_not_of("0123456789.-") != std::string::npos) {
    printError("invalid character in value.");
    return false;
  }
  if (value[0] == '.' || value[value.size() - 1] == '.' ||
      std::count(value.begin(), value.end(), '.') > 1 ||
      std::count(value.begin(), value.end(), '-') > 1) {
    printError("not a correct value format.");
    return false;
  }
  if (value[0] == '-') {
    printError("not a positive number.");
    return false;
  }
  double num = stringToDouble(value);
  if (num < 0) {
    printError("not a positive number.");
    return false;
  }
  if (1000.0 < num) {
    printError("too large a number.");
    return false;
  }
  return true;
}

double BitcoinExchange::getExchangeRate(const Date& date) {
  std::map<Date, double>::iterator it = _database.upper_bound(date);
  if (it == _database.begin()) return -1.0;
  --it;
  return it->second;
}

void BitcoinExchange::printResult(const std::string& date, double value,
                                  double rate) {
  std::cout << date << " => " << value << " = " << rate << std::endl;
}

void BitcoinExchange::printError(const std::string& message) {
  std::cerr << "Error: " << message << std::endl;
}

int BitcoinExchange::stringToInt(const std::string& str) {
  std::istringstream iss(str);
  int num;
  iss >> num;
  return num;
}

double BitcoinExchange::stringToDouble(const std::string& str) {
  std::istringstream iss(str);
  double num;
  iss >> num;
  return num;
}

std::string BitcoinExchange::doubleToString(double value) {
  std::ostringstream oss;
  oss << value;
  return oss.str();
}
