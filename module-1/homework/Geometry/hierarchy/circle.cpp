#include "circle.h"


double Circle::radius() const {
    return radius_;
}

Circle::Circle(const Point& center, double radius): Ellipse(center, center, radius * 2) {
    radius_ = radius;
}
