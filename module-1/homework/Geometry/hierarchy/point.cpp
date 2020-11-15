#include "point.h"
#include <cmath>
#include "constants.h"

bool Point::operator==(const Point& o) const {
  return x == o.x && y == o.y;
}

bool Point::operator!=(const Point& o) const {
  return !(*this == o);
}

Point::Point(double x, double y) : x(x), y(y) {}

Point Point::operator+(const Point& o) const {
  Point result = Point(*this);
  return result += o;
}

Point Point::operator-(const Point& o) const {
  Point result = Point(*this);
  return result -= o;
}

bool Point::operator<(const Point& rhs) const {
  return x < rhs.x || y < rhs.y;
}

Point& Point::operator+=(const Point& o) {
  return *this = {x + o.x, y + o.y};
}

Point& Point::operator-=(const Point& o) {
  return *this = {x - o.x, y - o.y};
}

double Point::distanceBetween(Point a, Point b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Point Point::operator*(double value) const {
  return {x * value, y * value};
}

void Point::rotate(Point& point, Point center, double angle) {
  angle = angle / 180.0 * GeometryConstants::PI;
  Point offset = point - center;
  Point middle{offset.x * cos(angle) - offset.y * sin(angle),
               offset.x * sin(angle) + offset.y * cos(angle)};
  point = middle + center;
}

void Point::scale(Point& point, Point center, double coefficient) {
  Point offset = point - center;
  Point scaled = offset * coefficient;
  point = center + scaled;
}
