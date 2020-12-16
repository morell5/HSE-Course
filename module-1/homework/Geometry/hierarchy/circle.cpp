#include "circle.h"

Circle::Circle(const Point& center, const double& r)
    : Ellipse(center, center, r * 2.0) {}

double Circle::radius() const {
    return (rade/2);
}

