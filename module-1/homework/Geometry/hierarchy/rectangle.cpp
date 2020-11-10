#include <utility>
#include <array>
#include <cmath>
#include "rectangle.h"

Rectangle::Rectangle(Point top, Point bottom, double sideRatio)
    : top(top), bottom(bottom), sideRatio(sideRatio) {

  double diagonal = Point::distanceBetween(top, bottom);
  double height = diagonal / sqrt(1 + sideRatio * sideRatio);
  double width = sqrt(diagonal * diagonal - height * height);

  Point topLeft = top - Point{width, 0};
  Point bottomLeft = top - Point{0, height};

  vtx = {top, topLeft, bottom, bottomLeft};
  m_center = (top + bottom) * 0.5;
}

Point Rectangle::center() const {
  return m_center;
}

std::pair<Line, Line> Rectangle::diagonals() const {
  Line straight = {top, bottom};
  Line alternate = {straight.a, -straight.b, straight.c};
  return {straight, alternate};
}

double Rectangle::getHeight() const {
  return Point::distanceBetween(top, bottom) * sqrt((1.0 - 1.0 / (1.0 + sideRatio)));
}

double Rectangle::getWidth() const {
  return Point::distanceBetween(top, bottom) / sqrt(1 + sideRatio);
}

