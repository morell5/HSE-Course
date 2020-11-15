#ifndef TGEO_SQUARE_H
#define TGEO_SQUARE_H

#include "circle.h"
#include "rectangle.h"

class Square : public Rectangle {
 public:
  Square(Point top, Point bottom);
  Circle circumscribedCircle() const;
  Circle inscribedCircle() const;
};

#endif