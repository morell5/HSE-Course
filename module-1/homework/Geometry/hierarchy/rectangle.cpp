#include "rectangle.h"

#include "line.h"
#include "point.h"

namespace bulumutka {

namespace {

std::vector<Point> createVertices(
    const Point& start,
    const Point& end,
    double coef
) {}

} // namespace

Rectangle::Rectangle(
    const Point& start,
    const Point& end, 
    double coef
) : Polygon(createVertices(start, end, coef)) {}

// Rectangle
Point Rectangle::center() const {

}

std::pair<Line, Line> Rectangle::diagonals() const {

}

// Polygon
bool Rectangle::operator==(const Shape& other) const {

}

}
