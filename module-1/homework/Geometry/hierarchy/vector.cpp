#include "vector.h"
#include <cmath>

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector::Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}

double Vector::length() const {
  return sqrt(x * x + y * y);
}

double Vector::angleBetween(const Vector& a, const Vector& b) {
  return atan2(a % b, a ^ b);
}

double Vector::operator^(const Vector& o) const {
  return x * o.x + y * o.y;
}

double Vector::operator%(const Vector& o) const {
  return x * o.y - y * o.x;
}

Vector Vector::normalized() const {
  return Vector{x / length(), y / length()};
}

Vector::operator Point() const {
  return {x, y};
}

Vector Vector::operator*(double value) const {
  return {value * x, value * y};
}