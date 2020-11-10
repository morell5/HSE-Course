#include "circle.h"

Circle::Circle(Point center, double radius) : Ellipse(center, center, radius * 2), m_radius(radius) {}

double Circle::radius() const {
  return m_radius;
};
