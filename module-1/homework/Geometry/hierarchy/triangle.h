#ifndef TGEO_TRIANGLE_H
#define TGEO_TRIANGLE_H

#include "circle.h"
#include "polygon.h"

class Triangle : public Polygon {
 public:
  Triangle(Point a, Point b, Point c);

  Circle circumscribedCircle() const;

  Circle inscribedCircle() const;

  Point getInnerCenter() const;

  Point getOuterCenter() const;

 private:
  Point a;
  Point b;
  Point c;
};

#endif