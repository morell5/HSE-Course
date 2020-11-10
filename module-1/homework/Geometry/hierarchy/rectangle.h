#ifndef TGEO_RECTANGLE_H
#define TGEO_RECTANGLE_H

#include "point.h"
#include "line.h"
#include "polygon.h"

class Rectangle : public Polygon {
private:
  Point top;
  Point bottom;
  double sideRatio;
protected:
  Point m_center;
public:
  Rectangle(Point top, Point bottom, double sideRatio);

  Point center() const;

  std::pair<Line, Line> diagonals() const;

  double getHeight() const;

  double getWidth() const;
};

#endif