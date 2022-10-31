#pragma once

#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

// Arbitrary-precision arithmetic representation of integers
namespace arbitrary_precision_arithmetic {
class Integer final {
 public:
  Integer();
  Integer(const Integer&);
  // Integer(Integer&&); // -__-

  Integer& operator=(const Integer&);
  // Integer& operator=(Integer&&);  // -__-

  // These constructors could be rewritten using templates
  // It's simple to use it in this task:
  // - Just try to use it,
  // - Remove repeating code &
  // - Don't forget to test it with different types
  // Oh, yeah, don't forget to specialize constructor from Integer type
  Integer(char unsigned);
  Integer(char);

  Integer(short unsigned);
  Integer(short);

  Integer(unsigned int);
  Integer(int);

  Integer(long unsigned);
  Integer(long);

  Integer(long long unsigned);
  Integer(long long);

  ~Integer();

  // arithmetic operators

  // arithmetic unary operators
  Integer operator-() const;
  Integer& operator--();
  Integer operator--(int);

  Integer operator+() const;
  Integer& operator++();
  Integer operator++(int);

  // arithmetic binary operators
  [[nodiscard]] Integer operator-(const Integer&) const;
  Integer& operator-=(const Integer&);

  [[nodiscard]] Integer operator+(const Integer&) const;
  Integer& operator+=(const Integer&);

  [[nodiscard]] Integer operator*(const Integer&) const;
  Integer& operator*=(const Integer&);

  [[nodiscard]] Integer operator/(const Integer&) const;
  Integer& operator/=(const Integer&);

  [[nodiscard]] Integer operator%(const Integer&) const;
  Integer& operator%=(const Integer&);

  // Conversion operators... Why don't you still use the templates?
  [[nodiscard]] explicit operator bool() const;
  [[nodiscard]] explicit operator unsigned char() const;
  [[nodiscard]] explicit operator char() const;
  [[nodiscard]] explicit operator unsigned short() const;
  [[nodiscard]] explicit operator short() const;
  [[nodiscard]] explicit operator unsigned int() const;
  [[nodiscard]] explicit operator int() const;
  [[nodiscard]] explicit operator unsigned long int() const;
  [[nodiscard]] explicit operator long int() const;
  [[nodiscard]] explicit operator unsigned long long int() const;
  [[nodiscard]] explicit operator long long int() const;

  // Comparators
  [[nodiscard]] bool operator==(const Integer&) const;
  [[nodiscard]] bool operator!=(const Integer&) const;
  [[nodiscard]] bool operator<(const Integer&) const;
  [[nodiscard]] bool operator<=(const Integer&) const;
  [[nodiscard]] bool operator>(const Integer&) const;
  [[nodiscard]] bool operator>=(const Integer&) const;
  // ...or you could read about operator<=> and implement it instead of
  // implementation of comparators above

  // Output stream print helper
  //  template <typename OStream>
  //  friend OStream&& operator<<(OStream&&, const Integer&);

  friend std::ostream& operator<<(std::ostream& os, const Integer& dt);
  friend std::istream& operator>>(std::istream& os, Integer& dt);

  Integer(const std::string& s);

  operator std::string() const;

  void shift_right();

  class divide_by_zero : public std::exception {};

 private:
  static const int BASE = 1000 * 1000 * 1000;
  std::vector<int32_t> lnum;
  bool conversionWarning = false;
};

// template <typename OStream>
// OStream&& operator<<(OStream&&, const Integer&) {
//   static_assert("Not implemented");
// }

// also you could implement your own string-literal for this type
// Integer ""_li(const char*);

}  // namespace arbitrary_precision_arithmetic
