#ifndef TGEO_CIRCLE_H
#define TGEO_CIRCLE_H

#include "ellipse.h"

class Circle : public Ellipse {
private:
  double m_radius{};
public:
  Circle(Point center, double radius);

  double radius() const;
};

#endif