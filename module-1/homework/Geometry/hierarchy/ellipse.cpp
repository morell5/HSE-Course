#include "ellipse.h"
#include "constants.h"
#include <cmath>

Ellipse::Ellipse(Point focusA, Point focusB, double radius)
    : focusA(focusA), focusB(focusB), a(radius / 2) {
  c = Point::distanceBetween(focusA, focusB) / 2;
  b = std::sqrt(a * a - c * c);
}

double Ellipse::perimeter() const {
  return 4 * (GeometryConstants::PI * a * b + (a - b)) / (a + b);
}

double Ellipse::area() const {
  return GeometryConstants::PI * a * b;
}


std::pair<Point, Point> Ellipse::focuses() const {
  return {focusA, focusB};
}

double Ellipse::eccentricity() const {
  return Ellipse::c / a;
}

Point Ellipse::center() const {
  return (focusA + focusB) * 0.5;
}

bool Ellipse::isCongruentTo(const Shape &o) const {
  const auto *ellipse = dynamic_cast<const Ellipse *>(&o);
  if (ellipse == nullptr) return false;
  return (fabs(Point::distanceBetween(focusA, focusB) -
               Point::distanceBetween(ellipse->focusA, ellipse->focusB)) < GeometryConstants::EPS) &&
         (fabs(a - ellipse->a) < GeometryConstants::EPS);
}

bool Ellipse::isSimilarTo(const Shape &o) const {
  const auto *ellipse = dynamic_cast<const Ellipse *>(&o);
  if (ellipse == nullptr) return false;
  double factor =
      Point::distanceBetween(focusA, focusB) / Point::distanceBetween(ellipse->focusA, ellipse->focusB);
  return fabs(a - ellipse->a * factor) < GeometryConstants::EPS;
}

bool Ellipse::containsPoint(Point point) const {
  return Point::distanceBetween(focusA, point) + Point::distanceBetween(focusB, point) <= 2 * a;
}

void Ellipse::rotate(Point center, double angle) {
  Point::rotate(focusA, center, angle);
  Point::rotate(focusB, center, angle);
}

void Ellipse::reflex(Line axis) {
  Line::reflexPoint(focusA, axis);
  Line::reflexPoint(focusB, axis);
}

void Ellipse::scale(Point center, double coefficient) {
  Point::scale(focusA, center, coefficient);
  Point::scale(focusB, center, coefficient);
}

std::pair<Line, Line> Ellipse::directries() const {
  auto focalParam = b * b / a;
  auto common = focalParam / (eccentricity() * (1 - eccentricity() * eccentricity()));
  return {
      {1, 0, common},
      {1, 0, -common}
  };
}

bool Ellipse::operator==(const Shape &o) const {
  const auto *ellipse = dynamic_cast<const Ellipse *>(&o);
  if (ellipse == nullptr) return false;
  return ((focusA == ellipse->focusA && focusB == ellipse->focusB) ||
          (focusA == ellipse->focusB && focusB == ellipse->focusA)) &&
         fabs(a - ellipse->a) < GeometryConstants::EPS;
}
