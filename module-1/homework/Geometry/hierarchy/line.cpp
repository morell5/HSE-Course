#include "line.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include "constants.h"

Line Line::normalized() const {
  Line line = {a, b, c};
  double coefficient = sqrt(a * a + b * b);
  line.a /= coefficient;
  line.b /= coefficient;
  line.c /= coefficient;

  return line;
}

bool Line::operator==(const Line& o) const {
  Line normalizedSelf = normalized();
  Line normalizedOther = o.normalized();

  return normalizedSelf.a == normalizedOther.a &&
         normalizedSelf.b == normalizedOther.b &&
         normalizedSelf.c == normalizedOther.c;
}

bool Line::operator!=(const Line& o) const {
  return !(*this == o);
}

Line::Line(double a, double b, double c) : a(a), b(b), c(c) {}

Line::Line(Point f, Point t) {
  a = f.y - t.y;
  b = t.x - f.x;
  c = f.x * t.y - t.x * f.y;
}

Vector Line::getNormalVector() const {
  return {a, b};
}

Point Line::operator()(double x) const {
  return {x, (c - a * x) / b};
}

double Line::pointDistance(Point point, Line line) {
  return std::abs(line.a * point.x + line.b * point.y + line.c) /
         std::sqrt(line.a * line.a + line.b * line.b);
}

std::int8_t Line::pointRelation(Point point, Line line) {
  if (fabs(line(point.x).y - point.y) < GeometryConstants::EPS)
    return 0;
  return point.y < line(point.x).y ? 1 : -1;
}

void Line::reflexPoint(Point& point, Line line) {
  auto distance = Line::pointDistance(point, line);
  Vector normal = line.getNormalVector().normalized();
  point += Point{normal * Line::pointRelation(point, line) * 2.0 * distance};
}

Line::IntersectResult Line::intersectLines(Line f, Line s) {
  if (f == s) {
    return {EQUAL, nullptr};
  } else {
    auto det = Vector{f.a, f.b} % Vector{s.a, s.b};
    if (fabs(det) < GeometryConstants::EPS)
      return {NONE, nullptr};

    auto* result = new Point(Vector{-f.c, f.b} % Vector{-s.c, s.b},
                             Vector{f.a, -f.c} % Vector{s.a, -s.c});
    return {POINT, result};
  }
}

Line Line::findBisector(Point p, Point a, Point b) {
  auto lengthPA = Point::distanceBetween(p, a);
  auto lengthPB = Point::distanceBetween(p, b);
  auto lambda = lengthPA / lengthPB;
  return {p,
          {(a.x + lambda * b.x) / (1 + lambda),
           (a.y + lambda * b.y) / (1 + lambda)}};
}
