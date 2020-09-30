#ifndef GEOMETRY_HIERARCHY_RECTANGLE_H_
#define GEOMETRY_HIERARCHY_RECTANGLE_H_

#include "polygon.h"


class Rectangle: public Polygon {
public:
    Rectangle(const Point& bottom_diag_pt, const Point& top_diag_pt, double factor);

    Point center() const;

    std::pair<Line, Line> diagonals() const;
};

#endif //GEOMETRY_HIERARCHY_RECTANGLE_H_