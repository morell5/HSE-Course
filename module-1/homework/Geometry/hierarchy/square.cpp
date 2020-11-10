#include <cmath>
#include "square.h"

Square::Square(Point top, Point bottom) : Rectangle(top, bottom, 1) {}

Circle Square::circumscribedCircle() const {
  return {m_center, getHeight() * sqrt(2) / 2.0};
}

Circle Square::inscribedCircle() const {
  return {m_center, getHeight() / 2};
}
