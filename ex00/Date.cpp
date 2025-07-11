#include "Date.hpp"

#include <sstream>
#include <iomanip>
#include <string>

// Orthodox canonical form
Date::Date(const std::string& str) {
  _rawString = str;
  _isValidFormat = false;
  _isValidDate = false;
  _year = -1;
  _month = -1;
  _day = -1;

  if (!isValidFormat(str)) {
    return;
  }
  _isValidFormat = true;
  _isValidDate = convertDate(str);
}

Date::~Date() {}

Date::Date(const Date& other) {
  _rawString = other._rawString;
  _isValidFormat = other._isValidFormat;
  _isValidDate = other._isValidDate;
  _year = other._year;
  _month = other._month;
  _day = other._day;
}

Date& Date::operator=(const Date& other) {
  if (this != &other) {
    _rawString = other._rawString;
    _isValidFormat = other._isValidFormat;
    _isValidDate = other._isValidDate;
    _year = other._year;
    _month = other._month;
    _day = other._day;
  }
  return *this;
}

// Member functions
bool Date::isValid() const {
  return _isValidFormat && _isValidDate;
}

bool Date::isValidFormat() const {
  return _isValidFormat;
}

bool Date::isValidDate() const {
  return _isValidDate;
}

std::string Date::toString() const {
  if (!isValid()) {
    return "Invalid date";
  }
  std::ostringstream oss;
  oss << std::setw(4) << std::setfill('0') << _year << "-"
      << std::setw(2) << std::setfill('0') << _month << "-"
      << std::setw(2) << std::setfill('0') << _day;
  return oss.str();
}

std::string Date::getRawString() const {
  return _rawString;
}

// Utility functions
bool Date::convertDate(const std::string& str) {
  if (!isValidFormat(str)) {
    return false;
  }

  std::istringstream iss_year(str.substr(0, 4));
  iss_year >> _year;
  std::istringstream iss_month(str.substr(5, 2));
  iss_month >> _month;
  std::istringstream iss_day(str.substr(8, 2));
  iss_day >> _day;

  if (!isValidDate(_year, _month, _day)) {
    return false;
  }
  return true;
}

bool Date::isValidFormat(const std::string& str) const {
  if (str.length() != 10) return false;
  for (size_t i = 0; i < str.length(); i++) {
    if (i == 4 || i == 7) {
      if (str[i] != '-')
        return false;
    } else if (!std::isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

bool Date::isValidDate(int year, int month, int day) const {
  if (year < 0 || month < 1 || 12 < month || day < 1 || 31 < day) {
    return false;
  }
  if (month == 2) {
    if (isLeapYear(year)) {
      return day <= 29;
    } else {
      return day <= 28;
    }
  }
  if (month == 4 || month == 6 || month == 9 || month == 11) {
    return day <= 30;
  }
  return true;
}

bool Date::isLeapYear(int year) const {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Comparison operators
bool Date::operator==(const Date& other) const {
  if (!_isValidDate || !other._isValidDate) return false;
  return _year == other._year && _month == other._month && _day == other._day;
}

bool Date::operator!=(const Date& other) const {
  if (!_isValidDate || !other._isValidDate) return true;
  return _year != other._year || _month != other._month || _day != other._day;
}

bool Date::operator<(const Date& other) const {
  if (!_isValidDate || !other._isValidDate) return false;
  return (_year < other._year) ||
         (_year == other._year && _month < other._month) ||
         (_year == other._year && _month == other._month && _day < other._day);
}

bool Date::operator<=(const Date& other) const {
  if (!_isValidDate || !other._isValidDate) return false;
  return *this < other || *this == other;
}

bool Date::operator>(const Date& other) const {
  if (!_isValidDate || !other._isValidDate) return false;
  return !(*this <= other);
}

bool Date::operator>=(const Date& other) const {
  if (!_isValidDate || !other._isValidDate) return false;
  return !(*this < other);
}
