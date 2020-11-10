#include "triangle.h"
#include "constants.h"
#include <stdexcept>
#include <numeric>
#include <cmath>

Triangle::Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {
  vtx = {a, b, c};
}

Circle Triangle::circumscribedCircle() const {
  auto sides = getSides();
  return Circle(getOuterCenter(), std::accumulate(sides.begin(), sides.end(), 1, std::multiplies<>()));
}

Circle Triangle::inscribedCircle() const {
  return Circle(getInnerCenter(), 2 * area() / perimeter());
}

Point Triangle::getInnerCenter() const {
  Line::IntersectResult result = Line::intersectLines(
      Line::findBisector(a, b, c),
      Line::findBisector(a, c, b));

  if (result.type != Line::POINT) throw std::logic_error("Cannot find an inscribed circle center");
  return *result.point;
}

Point Triangle::getOuterCenter() const {
  double d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
  if (fabs(d) < GeometryConstants::EPS) throw std::logic_error("Cannot find an circumscribed circle center");

  // O.O
  double ux = (a.x * a.x + a.y * a.y) * (b.y - c.y) + (b.x * b.x + b.y * b.y) * (c.y - a.y) +
              (c.x * c.x + c.y * c.y) * (a.y - b.y);
  double uy = (a.x * a.x + a.y * a.y) * (c.x - b.x) + (b.x * b.x + b.y * b.y) * (a.x - c.x) +
              (c.x * c.x + c.y * c.y) * (b.x - a.x);
  return {ux / d, uy / d};
}
