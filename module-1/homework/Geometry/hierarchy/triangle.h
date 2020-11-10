#ifndef TGEO_TRIANGLE_H
#define TGEO_TRIANGLE_H

#include "polygon.h"
#include "circle.h"

class Triangle : public Polygon {
private:
  Point a;
  Point b;
  Point c;

public:
  Triangle(Point a, Point b, Point c);

  Circle circumscribedCircle() const;

  Circle inscribedCircle() const;

  Point getInnerCenter() const;

  Point getOuterCenter() const;
};

#endif