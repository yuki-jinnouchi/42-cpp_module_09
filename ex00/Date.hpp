#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>

class Date {
 public:
  // Orthodox canonical form
  // MyDate();
  Date(const std::string& str);
  ~Date();
  Date(const Date& other);
  Date& operator=(const Date& other);

  // Member functions
  bool isValid() const;
  bool isValidFormat() const;
  bool isValidDate() const;
  std::string toString() const;
  std::string getRawString() const;

  // Comparison operators
  bool operator==(const Date& other) const;
  bool operator!=(const Date& other) const;
  bool operator<(const Date& other) const;
  bool operator<=(const Date& other) const;
  bool operator>(const Date& other) const;
  bool operator>=(const Date& other) const;

 private:
  std::string _rawString;
  bool _isValidFormat;
  bool _isValidDate;
  int _year;
  int _month;
  int _day;

  // Helper functions
  bool convertDate(const std::string& str);
  bool isValidFormat(const std::string& str) const;
  bool isValidDate(int year, int month, int day) const;
  bool isLeapYear(int year) const;
};

#endif  // DATE_HPP
