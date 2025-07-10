#include "BitcoinExchange.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

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
    std::string date;
    double rate;
    if (!std::getline(iss, date, ',') || !(iss >> rate)) {
      printError("invalid line format in database: " + line);
      break;
    }
    if (!isValidDate(date) || !isValidRate(doubleToString(rate))) {
      printError("invalid date or value in database: " + line);
      break;
    }
    _database[date] = rate;
  }
  file.close();

  if (_database.empty()) return false;
  return true;
}

void BitcoinExchange::processInputFile(const std::string& filename) {
  std::ifstream file(filename.c_str());  // 修正: c_str() を使用
  if (!file.is_open()) {
    printError("could not open file.");
    return;
  }

  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string date, valueStr;
    if (!std::getline(iss, date, '|') || !std::getline(iss, valueStr)) {
      printError("bad input => " + line);
      continue;
    }
    date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
    valueStr.erase(std::remove(valueStr.begin(), valueStr.end(), ' '),
                   valueStr.end());
    if (!isValidDate(date)) {
      printError("invalid date format => " + date);
      continue;
    }
    if (!isValidValue(valueStr)) {
      continue;
    }
    double value = stringToDouble(valueStr);
    double rate = getExchangeRate(date);
    if (rate < 0)
      printError("No exchange rate found for date => " + date);
    else
      printResult(date, value, rate * value);
  }
}

// Helper functions
bool BitcoinExchange::isValidDate(const std::string& date) {
  if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
  int year = stringToInt(date.substr(0, 4));
  int month = stringToInt(date.substr(5, 2));
  int day = stringToInt(date.substr(8, 2));
  if (year < 2009) return false;  // Bitcoin started in 2009
  if (month < 1 || 12 < month) return false;
  if (day < 1 || 31 < day) return false;
  return true;
}

bool BitcoinExchange::isValidRate(const std::string& rate) {
  if (rate.empty()) return false;
  if (rate[0] == '-') return false;
  if (rate.find_first_not_of("0123456789.") != std::string::npos) return false;
  return true;
}

bool BitcoinExchange::isValidValue(const std::string& value) {
  if (value.find_first_not_of("0123456789.-") != std::string::npos) {
    printError("invalid character in value.");
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

double BitcoinExchange::getExchangeRate(const std::string& date) {
  std::map<std::string, double>::iterator it = _database.lower_bound(date);
  if (it == _database.end()) return -1.0;
  if (it->first != date) --it;
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
