#include "Integer.hpp"

namespace arbitrary_precision_arithmetic {

Integer::Integer() { Integer::lnum.push_back(0); }

Integer::Integer(const Integer& b) { Integer::lnum = b.lnum; }

Integer& Integer::operator=(const Integer& b) {
  Integer::lnum = b.lnum;
  return *this;
}

Integer::Integer(char unsigned num) {
  if (!num) Integer::lnum.push_back(0);
  while (num) {
    Integer::lnum.push_back(num % Integer::BASE);
    num /= Integer::BASE;
  }
}

Integer::Integer(char num) {
  unsigned char number = num;
  bool negative = false;
  if (num < 0) {
    number = std::abs(num);
    negative = true;
  }
  if (!number) Integer::lnum.push_back(0);
  while (number) {
    Integer::lnum.push_back(number % Integer::BASE);
    number /= Integer::BASE;
  }
  if (negative) this->lnum.back() *= -1;
}

Integer::Integer(short unsigned num) {
  if (!num) Integer::lnum.push_back(0);
  while (num) {
    Integer::lnum.push_back(num % Integer::BASE);
    num /= Integer::BASE;
  }
}

Integer::Integer(short num) {
  unsigned short number = num;
  bool negative = false;
  if (num < 0) {
    number = std::abs(num);
    negative = true;
  }
  if (!number) Integer::lnum.push_back(0);
  while (number) {
    Integer::lnum.push_back(number % Integer::BASE);
    number /= Integer::BASE;
  }
  if (negative) this->lnum.back() *= -1;
}

Integer::Integer(unsigned int num) {
  if (!num) Integer::lnum.push_back(0);
  while (num) {
    Integer::lnum.push_back(num % Integer::BASE);
    num /= Integer::BASE;
  }
}

Integer::Integer(int num) {
  unsigned int number = num;
  bool negative = false;
  if (num < 0) {
    number = std::abs(num);
    negative = true;
  }
  if (!number) Integer::lnum.push_back(0);
  while (number) {
    Integer::lnum.push_back(number % Integer::BASE);
    number /= Integer::BASE;
  }
  if (negative) this->lnum.back() *= -1;
}

Integer::Integer(long unsigned num) {
  if (!num) Integer::lnum.push_back(0);
  while (num) {
    Integer::lnum.push_back(num % Integer::BASE);
    num /= Integer::BASE;
  }
}

Integer::Integer(long num) {
  unsigned long number = num;
  bool negative = false;
  if (num < 0) {
    number = std::abs(num);
    negative = true;
  }
  if (!number) Integer::lnum.push_back(0);
  while (number) {
    Integer::lnum.push_back(number % Integer::BASE);
    number /= Integer::BASE;
  }
  if (negative) {
    this->lnum.back() = -this->lnum.back();
  }
}

Integer::Integer(long long unsigned num) {
  if (!num) Integer::lnum.push_back(0);
  while (num) {
    Integer::lnum.push_back(num % Integer::BASE);
    num /= Integer::BASE;
  }
}

Integer::Integer(long long num) {
  unsigned long long number = num;
  bool negative = false;
  if (num < 0) {
    number = std::abs(num);
    negative = true;
  }
  if (!number) Integer::lnum.push_back(0);
  while (number) {
    Integer::lnum.push_back(number % Integer::BASE);
    number /= Integer::BASE;
  }
  if (negative) this->lnum.back() *= -1;
}

Integer::~Integer() = default;

Integer Integer::operator-() const {
  Integer res(*this);
  res.lnum.back() *= -1;
  return res;
}

Integer& Integer::operator--() {
  --Integer::lnum[0];
  return *this;
}

Integer Integer::operator--(int) {
  Integer temp(*this);
  --*this;
  return temp;
}

Integer Integer::operator+() const {
  Integer res(*this);
  return res;
}

Integer& Integer::operator++() {
  ++Integer::lnum[0];
  return *this;
}

Integer Integer::operator++(int) {
  Integer temp(*this);
  ++*this;
  return temp;
}

[[nodiscard]] Integer Integer::operator-(const Integer& b) const {
  Integer max = *this > b ? *this : b;
  Integer min = *this < b ? *this : b;
  Integer res(max);
  int32_t carry = 0;
  for (std::size_t i = 0; i < min.lnum.size() || carry; ++i) {
    res.lnum[i] -= carry + (i < min.lnum.size() ? min.lnum[i] : 0);
    carry = res.lnum[i] < 0;
    if (carry) res.lnum[i] += Integer::BASE;
  }
  return *this > b ? res : -res;
}

Integer& Integer::operator-=(const Integer& value) {
  *this = *this - value;
  return *this;
}

[[nodiscard]] Integer Integer::operator+(const Integer& b) const {
  Integer res(*this);
  int32_t carry = 0;
  for (int i = 0; i < std::max(res.lnum.size(), b.lnum.size()) || carry; ++i) {
    if (i == res.lnum.size()) {
      res.lnum.push_back(0);
    }
    res.lnum[i] += carry + (i < b.lnum.size() ? b.lnum[i] : 0);
    carry = res.lnum[i] >= BASE;
    if (carry) res.lnum[i] -= BASE;
  }
  return res;
}

Integer& Integer::operator+=(const Integer& value) {
  *this = *this + value;
  return *this;
}

[[nodiscard]] Integer Integer::operator*(const Integer& b) const {
  Integer res;
  res.lnum.resize(this->lnum.size() + b.lnum.size());
  for (std::size_t i = 0; i < this->lnum.size(); ++i) {
    int carry = 0;
    for (std::size_t j = 0; j < b.lnum.size() || carry; ++j) {
      long long cur =
          res.lnum[i + j] +
          this->lnum[i] * 1LL * (j < b.lnum.size() ? b.lnum[j] : 0) + carry;
      res.lnum[i + j] = static_cast<int>(cur % Integer::BASE);
      carry = static_cast<int>(cur / Integer::BASE);
    }
  }
  while (res.lnum.size() > 1 && res.lnum.back() == 0) {
    res.lnum.pop_back();
  }
  return res;
}

Integer& Integer::operator*=(const Integer& b) {
  *this = *this * b;
  return *this;
}

void Integer::shift_right() {
  if (this->lnum.empty()) {
    this->lnum.push_back(0);
    return;
  }
  this->lnum.push_back(this->lnum[this->lnum.size() - 1]);
  for (size_t i = this->lnum.size() - 2; i > 0; --i)
    this->lnum[i] = this->lnum[i - 1];
  this->lnum[0] = 0;
}

[[nodiscard]] Integer Integer::operator/(const Integer& right) const {
  if (right == 0) throw Integer::divide_by_zero();
  bool this_negative = this->lnum.back() < 0;
  bool right_negative = right.lnum.back() < 0;
  Integer b = right;
  Integer this_copy = *this;
  if (this_copy.lnum.back() < 0) {
    this_copy.lnum.back() *= -1;
  }
  if (b.lnum.back() < 0) {
    b.lnum.back() *= -1;
  }
  Integer result, current;
  result.lnum.resize(this_copy.lnum.size());
  for (long long i = static_cast<long long>(this_copy.lnum.size()) - 1; i >= 0;
       --i) {
    current.shift_right();
    current.lnum[0] = this_copy.lnum[i];
    while (current.lnum.size() > 1 && current.lnum.back() == 0) {
      current.lnum.pop_back();
    }
    int x = 0, l = 0, r = Integer::BASE;
    while (l <= r) {
      int m = (l + r) / 2;
      Integer t = b * m;
      if (t <= current) {
        x = m;
        l = m + 1;
      } else
        r = m - 1;
    }

    result.lnum[i] = x;
    current = current - b * x;
  }
  bool result_negative = (this_negative != right_negative);
  while (result.lnum.size() > 1 && result.lnum.back() == 0) {
    result.lnum.pop_back();
  }
  if (result_negative) {
    result.lnum.back() *= -1;
  }
  return result;
}

Integer& Integer::operator/=(const Integer& value) {
  *this = *this / value;
  return *this;
}

[[nodiscard]] Integer Integer::operator%(const Integer& b) const {
  Integer res = *this - (*this / b) * b;
  if (res < 0) res += b;
  while (res.lnum.size() > 1 && res.lnum.back() == 0) {
    res.lnum.pop_back();
  }
  return res;
}

Integer& Integer::operator%=(const Integer& value) {
  *this = *this % value;
  return *this;
}

[[nodiscard]] Integer::operator bool() const { return !(*this == 0); }

[[nodiscard]] Integer::operator unsigned char() const {
  unsigned char max = UCHAR_MAX;
  Integer uchar_max(max), zero(0);
  if (*this <= uchar_max && *this >= zero) {
    return this->lnum[0];
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this << " is out of 'unsigned char' range"
              << std::endl;
  }

  return max * (this->lnum.back() > 0 ? 1 : 0);
}

[[nodiscard]] Integer::operator char() const {
  char max = CHAR_MAX;
  char min = CHAR_MIN;
  Integer char_max(max), char_min(min);
  if (*this <= char_max && *this >= char_min) {
    return static_cast<char>(this->lnum[0]);
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this << " is out of 'char' range"
              << std::endl;
  }

  return static_cast<char>((max + (this->lnum.back() < 0 ? 1 : 0)) *
                           (this->lnum.back() < 0 ? -1 : 1));
}

[[nodiscard]] Integer::operator unsigned short() const {
  unsigned short max = USHRT_MAX;
  Integer ushort_max(max), zero(0);
  if (*this <= ushort_max && *this >= zero) {
    return this->lnum[0];
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this << " is out of 'unsigned short' range"
              << std::endl;
  }
  return max * (this->lnum.back() > 0 ? 1 : 0);
}

[[nodiscard]] Integer::operator short() const {
  short max = SHRT_MAX;
  short min = SHRT_MIN;
  Integer short_max(max), short_min(min);
  if (*this <= short_max && *this >= short_min) {
    return static_cast<short>(this->lnum[0]);
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this << " is out of 'short' range"
              << std::endl;
  }
  return static_cast<short>((max + (this->lnum.back() < 0 ? 1 : 0)) *
                            (this->lnum.back() < 0 ? -1 : 1));
}

[[nodiscard]] Integer::operator unsigned int() const {
  unsigned int max = UINT_MAX;
  Integer uint_max(max), zero(0);
  bool digits2 = this->lnum.size() == 2;
  if (*this <= uint_max && *this >= zero) {
    auto result = static_cast<unsigned int>(this->lnum[0]);
    auto second = static_cast<unsigned int>(
        (digits2 ? static_cast<unsigned int>(this->lnum[1]) * Integer::BASE
                 : 0));
    result += second;
    return result;
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this << " is out of 'unsigned int' range"
              << std::endl;
  }
  return max * (this->lnum.back() > 0 ? 1 : 0);
}

[[nodiscard]] Integer::operator int() const {
  int max = INT_MAX;
  int min = INT_MIN;
  Integer int_max(max), int_min(min);
  int negative = this->lnum.back() < 0 ? -1 : 1;
  bool digits2 = this->lnum.size() == 2;
  if (*this <= int_max && *this >= int_min) {
    return static_cast<int>(this->lnum[0] * negative +
                            (digits2 ? this->lnum[1] * Integer::BASE : 0));
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this << " is out of 'int' range" << std::endl;
  }
  if (this->lnum.back() < 0) {
    return INT_MIN;
  }
  return max;
}

[[nodiscard]] Integer::operator unsigned long int() const {
  unsigned long int max = ULONG_MAX;
  Integer ulong_max(max), zero(0);
  unsigned long digits = this->lnum.size();
  if (*this <= ulong_max && *this >= zero) {
    if (digits == 1) {
      return static_cast<unsigned long int>(this->lnum[0]);
    } else if (digits == 2) {
      return static_cast<unsigned long int>(
          this->lnum[0] +
          (static_cast<unsigned long>(this->lnum[1]) * Integer::BASE));
    } else {
      return static_cast<unsigned long int>(
          this->lnum[0] +
          (static_cast<unsigned long>(this->lnum[1]) * Integer::BASE) +
          (static_cast<unsigned long>(this->lnum[2]) * Integer::BASE *
           Integer::BASE));
    }
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this << " is out of 'unsigned long int' range"
              << std::endl;
  }
  return max * (this->lnum.back() > 0 ? 1 : 0);
}

[[nodiscard]] Integer::operator long int() const {
  long max = LONG_MAX;
  long min = LONG_MIN;
  Integer long_max(max), long_min(min);
  int negative = this->lnum.back() < 0 ? -1 : 1;
  unsigned long digits = this->lnum.size();
  if (*this <= long_max && *this >= long_min) {
    if (digits == 1) {
      return static_cast<long int>(this->lnum[0]);
    } else if (digits == 2) {
      return static_cast<long int>(
          this->lnum[0] * negative +
          (static_cast<long>(this->lnum[1]) * Integer::BASE));
    } else {
      return static_cast<long long>(
          this->lnum[0] * negative +
          (static_cast<long long>(this->lnum[1]) * Integer::BASE) * negative +
          (static_cast<long long>(this->lnum[2]) * Integer::BASE *
           Integer::BASE));
    }
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this << " is out of 'long int' range"
              << std::endl;
  }
  if (this->lnum.back() < 0) {
    return LONG_MIN;
  }
  return max;
}

[[nodiscard]] Integer::operator unsigned long long int() const {
  unsigned long long int max = ULLONG_MAX;
  Integer ullong_max(max), zero(0);
  unsigned long digits = this->lnum.size();
  if (*this <= ullong_max && *this >= zero) {
    if (digits == 1) {
      return static_cast<unsigned long long int>(this->lnum[0]);
    } else if (digits == 2) {
      return static_cast<unsigned long long int>(
          this->lnum[0] +
          (static_cast<unsigned long long int>(this->lnum[1]) * Integer::BASE));
    } else {
      return static_cast<unsigned long long int>(
          this->lnum[0] +
          (static_cast<unsigned long long int>(this->lnum[1]) * Integer::BASE) +
          (static_cast<unsigned long long int>(this->lnum[2]) * Integer::BASE *
           Integer::BASE));
    }
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this
              << " is out of 'unsigned long long int' range" << std::endl;
  }
  return max * (this->lnum.back() > 0 ? 1 : 0);
}

[[nodiscard]] Integer::operator long long int() const {
  long long int max = LLONG_MAX;
  long long int min = LLONG_MIN;
  Integer llong_max(max), llong_min(min);
  int negative = this->lnum.back() < 0 ? -1 : 1;
  unsigned long digits = this->lnum.size();
  if (*this <= llong_max && *this >= llong_min) {
    if (digits == 1) {
      return static_cast<long long int>(this->lnum[0]);
    } else if (digits == 2) {
      return static_cast<long long int>(
          this->lnum[0] * negative +
          (static_cast<long long int>(this->lnum[1]) * Integer::BASE));
    } else {
      return static_cast<long long int>(
          this->lnum[0] * negative +
          (static_cast<long long int>(this->lnum[1]) * Integer::BASE) *
              negative +
          (static_cast<long long int>(this->lnum[2]) * Integer::BASE *
           Integer::BASE));
    }
  }
  if (conversionWarning) {
    std::clog << "Conversion warning: "
              << "the value " << *this << " is out of 'long long int' range"
              << std::endl;
  }
  if (this->lnum.back() < 0) {
    return LLONG_MIN;
  }
  return max;
}

[[nodiscard]] bool Integer::operator==(const Integer& b) const {
  if (this->lnum.size() != b.lnum.size()) {
    return false;
  }
  for (int i = 0; i < this->lnum.size(); ++i) {
    if (this->lnum[i] != b.lnum[i]) {
      return false;
    }
  }
  return true;
}

[[nodiscard]] bool Integer::operator!=(const Integer& b) const {
  return !(*this == b);
}

[[nodiscard]] bool Integer::operator<(const Integer& b) const {
  if (*this == b) return false;
  bool negative_this, negative_b;
  negative_this = this->lnum.back() < 0;
  negative_b = b.lnum.back() < 0;
  if (negative_this) {
    if (negative_b)
      return ((-b) < (-*this));
    else
      return true;
  } else if (negative_b)
    return false;
  else {
    if (this->lnum.size() != b.lnum.size()) {
      return this->lnum.size() < b.lnum.size();
    } else {
      for (int i = static_cast<int>(this->lnum.size() - 1); i >= 0; --i) {
        if (this->lnum[i] != b.lnum[i]) {
          return this->lnum[i] < b.lnum[i];
        }
      }
      return false;
    }
  }
}

[[nodiscard]] bool Integer::operator<=(const Integer& b) const {
  return (*this < b || *this == b);
}

[[nodiscard]] bool Integer::operator>(const Integer& b) const {
  return !(*this <= b);
}

[[nodiscard]] bool Integer::operator>=(const Integer& b) const {
  return !(*this < b);
}

std::ostream& operator<<(std::ostream& os, const Integer& b) {
  os << (b.lnum.empty() ? 0 : b.lnum.back());
  for (int i = static_cast<int>(b.lnum.size()) - 2; i >= 0; --i) {
    os << std::setw(9) << std::setfill('0') << b.lnum[i];
  }
  return os;
}

std::istream& operator>>(std::istream& os, Integer& dt) {
  std::string s;
  os >> s;
  if (s.front() == '\"' && s.back() == '\"') {
    s.front() = '0';
    s.pop_back();
  }
  Integer result(s);
  dt = result;
  return os;
}

Integer::Integer(const std::string& s) {
  for (int i = static_cast<int>(s.length()); i > 0; i -= 9) {
    if (i < 9) {
      lnum.push_back(atoi(s.substr(0, i).c_str()));
    } else {
      lnum.push_back(atoi(s.substr(i - 9, 9).c_str()));
    }
  }
  while (this->lnum.size() > 1 && this->lnum.back() == 0) {
    this->lnum.pop_back();
  }
}

Integer::operator std::string() const {
  std::stringstream sream;
  sream << *this;
  return sream.str();
}

}  // namespace arbitrary_precision_arithmetic
