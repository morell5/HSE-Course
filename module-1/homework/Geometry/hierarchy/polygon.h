#ifndef TGEO_POLYGON_H
#define TGEO_POLYGON_H

#include "shape.h"
#include "point.h"
#include <vector>

class Polygon : public Shape {
public:
  Polygon() = default;

  explicit Polygon(std::vector<Point> points);

  Polygon(const std::initializer_list<Point> &points);

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

  std::size_t verticesCount() const;

  const std::vector<Point> &getVertices() const;

  bool isConvex() const;

  std::vector<double> getSides() const;

  std::vector<double> getAngles() const;

  bool operator==(const Shape &o) const override;

protected:
  std::vector<Point> vtx;
};

#endif