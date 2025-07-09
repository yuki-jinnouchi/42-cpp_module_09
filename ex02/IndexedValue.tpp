#ifndef INDEXED_VALUE_TPP
#define INDEXED_VALUE_TPP

#include <cstddef>
#include <iostream>
#include <string>

// Orthodox Canonical Form
template <typename T>
IndexedValue<T>::IndexedValue() : _value(T()), _index(0) {}

template <typename T>
IndexedValue<T>::IndexedValue(const T &value, size_t index) : _value(value) {
  _index.push_back(index);
}

template <typename T>
IndexedValue<T>::~IndexedValue() {}

template <typename T>
IndexedValue<T>::IndexedValue(const IndexedValue<T> &other)
    : _value(other._value), _index(other._index) {}

template <typename T>
IndexedValue<T> &IndexedValue<T>::operator=(const IndexedValue<T> &other) {
  if (this != &other) {
    _value = other._value;
    _index = other._index;
  }
  return *this;
}

// Accessor methods
template <typename T>
void IndexedValue<T>::pushIndex(size_t index) {
  _index.push_back(index);
}

template <typename T>
size_t IndexedValue<T>::getIndex() const {
  if (_index.empty()) {
    return 0;
  }
  return _index.back();
}

template <typename T>
size_t IndexedValue<T>::popIndex() {
  if (_index.empty()) {
    return 0;
  }
  size_t index = _index.back();
  _index.pop_back();
  return index;
}

// Comparison operators for IndexedValue
template <typename T>
bool IndexedValue<T>::operator<(const IndexedValue &other) const {
  return _value < other._value;
}

template <typename T>
bool IndexedValue<T>::operator>(const IndexedValue &other) const {
  return _value > other._value;
}

template <typename T>
bool IndexedValue<T>::operator<=(const IndexedValue &other) const {
  return _value <= other._value;
}

template <typename T>
bool IndexedValue<T>::operator>=(const IndexedValue &other) const {
  return _value >= other._value;
}

template <typename T>
bool IndexedValue<T>::operator==(const IndexedValue &other) const {
  return _value == other._value;
}

template <typename T>
bool IndexedValue<T>::operator!=(const IndexedValue &other) const {
  return _value != other._value;
}

template <typename T>
std::ostream &operator<<(std::ostream &os,
                         const IndexedValue<T> &indexedValue) {
  os << indexedValue._value << "(" << indexedValue.getIndex() << ")";
  return os;
}

#endif  // INDEXED_VALUE_TPP
