#include "polygon.h"
#include <utility>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include "constants.h"
#include "point.h"
#include "vector.h"

Polygon::Polygon(std::vector<Point> points) : vtx(std::move(points)) {}

Polygon::Polygon(const std::initializer_list<Point> &points) {
  for (const auto &i : points)
    vtx.push_back(i);
}

std::size_t Polygon::verticesCount() const {
  return vtx.size();
}

const std::vector<Point> &Polygon::getVertices() const {
  return vtx;
}

bool Polygon::isConvex() const {
  if (vtx.size() < 3)
    return false;

  Point a = vtx[0];
  Point b = vtx[1];
  Point c = vtx[2];
  bool sign = (Vector{a, b} % Vector{b, c}) < GeometryConstants::EPS;

  for (std::size_t i = 1; i < vtx.size(); i++) {
    a = vtx[i % vtx.size()];
    b = vtx[(i + 1) % vtx.size()];
    c = vtx[(i + 2) % vtx.size()];

    if ((Vector{a, b} % Vector{b, c} < GeometryConstants::EPS) != sign)
      return false;
  }

  return true;
}

double Polygon::perimeter() const {
  double perimeter = 0;
  for (std::size_t i = 0; i < vtx.size(); i++) {
    Point a = vtx[i];
    Point b = vtx[(i + 1) % verticesCount()];

    perimeter += Vector{a, b}.length();
  }

  return perimeter;
}

double Polygon::area() const {
  double area = 0;
  Point root = vtx.front();

  for (std::size_t i = 1; i < vtx.size() - 1; i++) {
    Point b = vtx[i];
    Point c = vtx[i + 1];

    area += Vector{root, b} % Vector{root, c} / 2.0;
  }

  return fabs(area);
}

//TODO: Implement NOT WORKING
bool Polygon::isCongruentTo(const Shape &o) const {
  const auto *polygon = dynamic_cast<const Polygon *>(&o);
  if (polygon == nullptr)
    return false;

  if (polygon->verticesCount() != verticesCount()) return false;

  std::vector<double> allSelf = getSides();
  auto anglesSelf = getAngles();
  std::copy (anglesSelf.begin(), anglesSelf.end(), std::back_inserter(allSelf));
  std::sort(allSelf.begin(), allSelf.end());

  std::vector<double> allOther = polygon->getSides();
  auto anglesOther = polygon->getAngles();
  std::copy (anglesOther.begin(), anglesOther.end(), std::back_inserter(allOther));
  std::sort(allOther.begin(), allOther.end());

  for (std::size_t i = 0; i < allSelf.size(); i++) {
    auto self = allSelf[i];
    auto other = allOther[i];

    if (std::fabs(other - self) > GeometryConstants::EPS) return false;
  }

  return true;
}

//TODO: Implement
bool Polygon::isSimilarTo(const Shape &o) const {
  const auto *polygon = dynamic_cast<const Polygon *>(&o);
  if (polygon == nullptr)
    return false;

  if (polygon->verticesCount() != verticesCount()) return false;

  auto selfSides = getSides();
  auto otherSides = polygon->getSides();

  auto primaryRatio = selfSides.front() / otherSides.front();
  for (std::size_t i = 0; i < selfSides.size(); i++) {
    if (std::fabs(selfSides[i] / otherSides[i] - primaryRatio) > GeometryConstants::EPS) return false;
  }

  auto selfAngles = getAngles();
  auto otherAngles = polygon->getAngles();
  std::sort(selfSides.begin(), selfSides.end());
  std::sort(otherAngles.begin(), otherAngles.end());

  return selfAngles == otherAngles;
}

bool Polygon::containsPoint(Point point) const {
  double angleSum = 0;
  for (std::size_t i = 0; i < vtx.size(); i++) {
    Point a{vtx[i]};
    Point b{vtx[(i + 1) % vtx.size()]};

    angleSum += Vector::angleBetween({point, a}, {point, b});
    if (Vector{point, a}.length() + Vector{point, b}.length() - Vector{a, b}.length() < GeometryConstants::EPS) {
      return true;
    }
  }

  angleSum = std::abs(angleSum);
  return std::abs(angleSum - 2 * GeometryConstants::PI) < GeometryConstants::EPS;
}

bool Polygon::operator==(const Shape &o) const {
  const auto *polygon = dynamic_cast<const Polygon *>(&o);
  if (polygon == nullptr)
    return false;

  return
      std::all_of(polygon->vtx.begin(), polygon->vtx.end(), [this](const auto &p) { return this->containsPoint(p); }) &&
      std::all_of(vtx.begin(), vtx.end(), [&polygon](const auto &p) { return polygon->containsPoint(p); });
}

void Polygon::rotate(Point center, double angle) {
  for (auto &point : vtx) {
    Point::rotate(point, center, angle);
  }
}

void Polygon::reflex(Line axis) {
  for (auto &point : vtx) {
    Line::reflexPoint(point, axis);
  }
}

void Polygon::scale(Point center, double coefficient) {
  for (auto &point : vtx) {
    Point::scale(point, center, coefficient);
  }
}

std::vector<double> Polygon::getSides() const {
  std::vector<double> result;
  for (std::size_t i = 0; i < vtx.size(); i++) {
    Point a = vtx[i];
    Point b = vtx[(i + 1) % vtx.size()];
    result.push_back(Point::distanceBetween(a, b));
  }

  return result;
}

std::vector<double> Polygon::getAngles() const {
  std::vector<double> result;
  for (std::size_t i = 0; i < vtx.size(); i++) {
    Point a = vtx[i];
    Point b = vtx[(i + 1) % vtx.size()];
    Point c = vtx[(i + 2) % vtx.size()];

    result.push_back(Vector::angleBetween({a, b}, {c, b}));
  }

  return result;
}

