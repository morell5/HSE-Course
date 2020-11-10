#ifndef TGEO_SQUARE_H
#define TGEO_SQUARE_H

#include "rectangle.h"
#include "circle.h"

class Square : public Rectangle {
public:
  Square(Point top, Point bottom);
  Circle circumscribedCircle() const;
  Circle inscribedCircle() const;
};

#endif