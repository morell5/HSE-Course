#ifndef TGEO_LINE_H
#define TGEO_LINE_H

#include "point.h"
#include "vector.h"
#include <cstdint>

struct Line {
  // Line coefficients: a * x + b * y = c
  double a{0.0};
  double b{0.0};
  double c{0.0};

  Line() = default;

  Line(double a, double b, double c);

  Line(Point a, Point b);

  // Normalized form of line
  Line normalized() const;

  // Get leading vector of the line
  // (-b, a)
  Vector getLeadingVector() const;

  // Get normal to leading vector
  // (a, b)
  Vector getNormalVector() const;

  bool operator==(const Line &o) const;

  bool operator!=(const Line &o) const;

  // Returns point on line for arbitrary x
  Point operator()(double x) const;

  static double pointDistance(Point point, Line line);

  static void reflexPoint(Point &point, Line line);

  enum IntersectResultType {
    NONE, EQUAL, POINT
  };

  struct IntersectResult {
    IntersectResultType type;
    Point * point;
  };

  static IntersectResult intersectLines(Line first, Line second);
  static Line findBisector(Point p, Point a, Point b);

  /**
   * Determine point relation to line
   * @param point to determine for
   * @param line to determine for
   * @return -1 if is higher, 1 if is lower, 0 if point lies in line
   */
  static std::int8_t pointRelation(Point point, Line line);
};

#endif