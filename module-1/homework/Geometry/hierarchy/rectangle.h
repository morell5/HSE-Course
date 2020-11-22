#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "polygon.h"

#include <utility>

namespace bulumutka {

class Line;
class Point;

class Rectangle : public Polygon {
public:
    Rectangle(const Point& start, const Point& end, double coef);

    virtual ~Rectangle() override {};

    // Rectangle
    virtual Point center() const;
    virtual std::pair<Line, Line> diagonals() const;

    // Polygon
    virtual bool operator==(const Shape& other) const override;
};

}

#endif
