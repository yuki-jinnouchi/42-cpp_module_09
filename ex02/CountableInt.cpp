#include "CountableInt.hpp"

#include <iostream>

// Static member initialization
int CountableInt::_comparison_count = 0;

// Orthodox Canonical Form
CountableInt::CountableInt() : _value(0) {}

CountableInt::CountableInt(int value) : _value(value) {}

CountableInt::~CountableInt() {}

CountableInt::CountableInt(const CountableInt &other) : _value(other._value) {}

CountableInt &CountableInt::operator=(const CountableInt &other) {
  if (this != &other) {
    _value = other._value;
  }
  return *this;
}

// operator overloading
bool CountableInt::operator<(const CountableInt &other) const {
  _comparison_count++;
  // std::cout << "< ";
  return _value < other._value;
}

bool CountableInt::operator>(const CountableInt &other) const {
  _comparison_count++;
  // std::cout << "> ";
  return _value > other._value;
}

bool CountableInt::operator<=(const CountableInt &other) const {
  _comparison_count++;
  // std::cout << "<= ";
  return _value <= other._value;
}

bool CountableInt::operator>=(const CountableInt &other) const {
  _comparison_count++;
  // std::cout << ">= ";
  return _value >= other._value;
}

bool CountableInt::operator==(const CountableInt &other) const {
  _comparison_count++;
  // std::cout << "== ";
  return _value == other._value;
}

bool CountableInt::operator!=(const CountableInt &other) const {
  _comparison_count++;
  // std::cout << "!= ";
  return _value != other._value;
}


int CountableInt::getValue() const {
  return _value;
}

CountableInt::operator int() const {
  return _value;
}

void CountableInt::resetCount() {
  _comparison_count = 0;
}

int CountableInt::getComparisonCount() {
  return _comparison_count;
}
