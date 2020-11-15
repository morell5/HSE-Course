#ifndef TGEO_RECTANGLE_H
#define TGEO_RECTANGLE_H

#include "line.h"
#include "point.h"
#include "polygon.h"

class Rectangle : public Polygon {
 public:
  Rectangle(Point top, Point bottom, double sideRatio);

  Point center() const;

  std::pair<Line, Line> diagonals() const;

  double getHeight() const;

  double getWidth() const;

 protected:
  Point m_center;

 private:
  Point top;
  Point bottom;
  double sideRatio;
};

#endif