#ifndef TGEO_ELLIPSE_H
#define TGEO_ELLIPSE_H

#include "shape.h"
#include <vector>

class Ellipse : public Shape {
private:
  Point focusA;
  Point focusB;
  double a;
  double b;
  double c;

public:
  Ellipse(Point a, Point b, double radius);

  double perimeter() const override;

  double area() const override;

  bool isCongruentTo(const Shape &o) const override;

  bool isSimilarTo(const Shape &o) const override;

  bool containsPoint(Point point) const override;

  // @angle measures up to degrees
  void rotate(Point center, double angle) override;

  // FlEx
  void reflex(Line axis) override;

  void scale(Point center, double coefficient) override;

  std::pair<Point, Point> focuses() const;

  std::pair<Line, Line> directries() const;

  double eccentricity() const;

  Point center() const;

  bool operator==(const Shape& o) const override;
};

#endif