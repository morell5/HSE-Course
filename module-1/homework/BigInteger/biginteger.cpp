//
// Created by kimigaev on 21.09.2020.
//

#include "biginteger.h"
uint32_t BigInteger::vector_at(const std::vector<uint32_t> &vec, size_t index) {
  return vec.size() > index ? vec[index] : 0;
}
BigInteger BigInteger::Add(const BigInteger &num1, const BigInteger &num2, int32_t sign) {
  BigInteger temp;
  temp.sign_ = sign;
  size_t size = std::max(num1.data_.size(), num2.data_.size()) + 1;
  temp.data_.resize(size);
  uint64_t now = 0;
  for (size_t i = 0; i < size; ++i) {
    now += vector_at(num1.data_, i) + vector_at(num2.data_, i);
    temp.data_[i] = now % MAX;
    now /= MAX;
  }
  while (temp.data_.back() == 0 && temp.data_.size() > 1) temp.data_.pop_back();
  if (temp.data_.size() == 1 && temp.data_.back() == 0) temp.sign_ = 1;
  return temp;
}
BigInteger BigInteger::Sub(BigInteger num1, BigInteger num2, int32_t sign) {
  BigInteger temp;
  size_t size = std::max(num1.data_.size(), num2.data_.size()) + 1;
  temp.data_.resize(size);
  int64_t now = 0;
  if (num1.IsLess(num2)) {
    num1.Swap(num2);
    sign = -sign;
  }
  temp.sign_ = sign;
  for (size_t i = 0; i < size; ++i) {
    now += (int64_t) vector_at(num1.data_, i) - (int64_t) vector_at(num2.data_, i);
    if (now < 0) {
      temp.data_[i] = (int32_t) MAX + now;
      now = -1;
    } else {
      temp.data_[i] = now;
      now = 0;
    }
  }
  while (temp.data_.back() == 0 && temp.data_.size() > 1) temp.data_.pop_back();
  if (temp.data_.size() == 1 && temp.data_.back() == 0) temp.sign_ = 1;
  return temp;
}
std::pair<BigInteger, BigInteger> BigInteger::BigDivMod(const BigInteger &numerator, const BigInteger &denominator) {
  //not implemented exception
  throw std::range_error("denominator");
}
std::pair<BigInteger, BigInteger> BigInteger::DivMod(const BigInteger &numerator, const BigInteger &denominator) {
  if (denominator >= MAX || denominator <= -MAX) return BigDivMod(numerator, (BigInteger) denominator);
  BigInteger temp = numerator;
  temp.sign_ = numerator.sign_ * denominator.sign_;
  if (denominator == 0) throw std::runtime_error("denominator is zero");
  if (numerator == 0) return {{}, {}};
  int32_t carry = 0;
  for (int32_t i = (int32_t) temp.data_.size() - 1; i >= 0; --i) {
    int64_t cur = temp.data_[i] + (int64_t) carry * MAX;
    temp.data_[i] = (uint32_t) (cur / denominator.data_[0]);
    carry = (int32_t) cur % denominator.data_[0];
  }
  while (temp.data_.size() > 1 && temp.data_.back() == 0)
    temp.data_.pop_back();
  if (temp.sign_ == -1) carry = -carry;
  if (temp.data_.size() == 1 && temp.data_.back() == 0) temp.sign_ = 1;
  return {temp, carry};
}
bool BigInteger::IsLess(const BigInteger &num) const {
  size_t size = std::max(this->data_.size(), num.data_.size());
  for (size_t i = size - 1; i >= 0; --i) {
    if (vector_at(this->data_, i) < vector_at(num.data_, i)) return true;
    if (vector_at(this->data_, i) > vector_at(num.data_, i)) return false;
  }
  return false;
}
BigInteger::BigInteger(const std::string &st) {
  auto str = st;
  if (str.empty()) return;
  if (str[0] == '-') sign_ = -1;
  auto begin = 0;
  for (auto i : str) {
    if (i == '0' || i == '-') ++begin;
    else break;
  }
  if (begin == str.size()) return;
  data_.clear();
  while (str.size() > begin) {
    std::string tmp(str.c_str() + std::max(begin, (int32_t) str.size() - 9));
    data_.emplace_back(std::stoul(tmp, nullptr, 10));
    for (int i = 0; i < tmp.size(); ++i) str.pop_back();
  }
}
BigInteger::BigInteger(const BigInteger &num) {
  *this = num;
}
BigInteger::BigInteger(const int64_t &num) {
  *this = num;
}
bool BigInteger::operator==(const BigInteger &num) const {
  return (sign_ == num.sign_ && data_ == num.data_);
}
bool BigInteger::operator!=(const BigInteger &num) const {
  return !(*this == num);
}
bool BigInteger::operator<(const BigInteger &num) const {
  if (this->sign_ < num.sign_) return true;
  if (this->sign_ > num.sign_) return false;
  return this->sign_ > 0 ? IsLess(num) : !IsLess(num);
}
bool BigInteger::operator>(const BigInteger &num) const {
  return !(*this < num || *this == num);
}
bool BigInteger::operator<=(const BigInteger &num) const {
  return *this < num || *this == num;
}
bool BigInteger::operator>=(const BigInteger &num) const {
  return !(*this < num);
}
BigInteger BigInteger::operator+(const BigInteger &num) const {
  if (sign_ + num.sign_ == 0) {
    return Sub(*this, num, sign_);
  } else return Add(*this, num, sign_);
}
BigInteger BigInteger::operator-(const BigInteger &num) const {
  return *this + (-num);
}
BigInteger BigInteger::operator*(const BigInteger &num) {
  BigInteger t2;
  BigInteger temp;
  uint64_t now = 0;
  for (size_t i = 0; i < data_.size(); ++i) {
    for (size_t j = 0; j < num.data_.size(); ++j) {
      now += (uint64_t) data_[i] * num.data_[j];
      if (temp.data_.size() <= i + j) temp.data_.resize(i + j + 1);
      temp.data_[i + j] = now % MAX;
      now /= (uint64_t) MAX;
    }
    if (now > 0) {
      if (temp.data_.size() <= i + num.data_.size()) temp.data_.resize(i + num.data_.size() + 1);
      temp.data_[i + num.data_.size()] = now;
      now = 0;
    }
    t2 += temp;
    temp = 0;
  }
  if (sign_ != num.sign_) t2.sign_ = -1;
  return t2;
}
BigInteger BigInteger::operator/(const BigInteger &num) const {
  return DivMod(*this, num).first;
}
BigInteger BigInteger::operator%(const BigInteger &num) const {
  return DivMod(*this, num).second;
}
BigInteger &BigInteger::operator/=(const BigInteger &num) {
  return (*this = DivMod(*this, num).first);
}
BigInteger &BigInteger::operator%=(const BigInteger &num) {
  return (*this = DivMod(*this, num).second);
}
BigInteger &BigInteger::operator*=(const BigInteger &num) {
  return *this = *this * num;
}
BigInteger &BigInteger::operator+=(const BigInteger &num) {
  return (*this = *this + num);
}
BigInteger &BigInteger::operator-=(const BigInteger &num) {
  return (*this = *this - num);
}
BigInteger BigInteger::operator++(int) {
  auto temp = *this;
  *this += 1;
  return temp;
}
BigInteger BigInteger::operator--(int) {
  auto temp = *this;
  *this -= 1;
  return temp;
}
BigInteger &BigInteger::operator++() {
  if ((sign_ == 1 && data_.front() == MAX - 1)
      || (sign_ == -1 && data_.front() == 0))
    return *this += 1;
  if (sign_ == 1) data_.front()++;
  if (sign_ == -1) data_.front()--;
  return *this;
}
BigInteger &BigInteger::operator--() {
  if ((sign_ == -1 && data_.front() == MAX - 1)
      || (sign_ == 1 && data_.front() == 0))
    return *this -= 1;
  if (sign_ == -1) data_.front()++;
  if (sign_ == 1) data_.front()--;
  return *this;
}
void BigInteger::Swap(BigInteger &num) {
  std::swap(sign_, num.sign_);
  std::swap(data_, num.data_);
}
BigInteger::operator bool() {
  return !(*this == BigInteger(0));
}
BigInteger &BigInteger::operator=(int32_t num) {
  if (num < 0)
    sign_ = -1;
  data_ = std::vector<uint32_t>{(uint32_t) std::abs(num)};
  return *this;
}
BigInteger BigInteger::operator-() const {
  auto copy = *this;
  copy.sign_ = -sign_;
  return copy;
}
int32_t BigInteger::GetSign() const {
  return sign_;
}
std::string BigInteger::toString() const {
  std::string s;
  if (sign_ == -1) s.push_back('-');
  bool f = false;
  for (auto i = data_.rbegin(); i != data_.rend(); ++i) {
    if (*i == 0 and !f) continue;
    auto now = std::to_string(*i);
    if (f) s.append(std::string(9 - now.size(), '0'));
    s.append(now);
    f = true;
  }
  if (s.empty()) s = '0';
  return s;
}
std::istream &operator>>(std::istream &in, BigInteger &num) {
  std::string str;
  in >> str;
  num = str;
  return in;
}
std::ostream &operator<<(std::ostream &out, const BigInteger &num) {
  out << num.toString();
  return out;
}
BigInteger Abs(const BigInteger &num) {
  return num.GetSign() == 1 ? num : -num;
}
void swap(BigInteger &num1, BigInteger &num2) {
  num1.Swap(num2);
}
