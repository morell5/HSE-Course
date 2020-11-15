#ifndef TGEO_VECTOR_H
#define TGEO_VECTOR_H

#include "point.h"

struct Vector {
  double x{0.0};
  double y{0.0};

  Vector() = default;

  // Vector from it's coordinates
  Vector(double x, double y);

  // Vector from point a to point b
  Vector(Point a, Point b);

  // Length of the vector
  double length() const;

  // Normalize vector
  Vector normalized() const;

  // Scalar product
  double operator^(const Vector& o) const;

  // Cross product
  double operator%(const Vector& o) const;

  // Multiply (scale)
  Vector operator*(double value) const;

  // To point
  explicit operator Point() const;

  // Angle between self and other vector
  static double angleBetween(const Vector& a, const Vector& b);
};

#endif