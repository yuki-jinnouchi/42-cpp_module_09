#ifndef INDEXED_VALUE_HPP
#define INDEXED_VALUE_HPP

#include <cstddef>
#include <iostream>

template <typename T>
class IndexedValue {
 public:
  T _value;
  std::vector<size_t> _index;

  // Orthodox Canonical Form
  IndexedValue();
  IndexedValue(const T &value, size_t index);
  ~IndexedValue();
  IndexedValue(const IndexedValue &other);
  IndexedValue &operator=(const IndexedValue &other);

  // Comparison operator for sorting
  bool operator<(const IndexedValue &other) const;
  bool operator>(const IndexedValue &other) const;
  bool operator<=(const IndexedValue &other) const;
  bool operator>=(const IndexedValue &other) const;
  bool operator==(const IndexedValue &other) const;
  bool operator!=(const IndexedValue &other) const;

  // Accessor methods
  void pushIndex(size_t index);
  size_t getIndex() const;
  size_t popIndex();

};

template <typename T>
std::ostream &operator<<(std::ostream &os, const IndexedValue<T> &indexedValue);

#include "IndexedValue.tpp"

#endif  // INDEXED_VALUE_HPP
