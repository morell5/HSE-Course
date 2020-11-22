#include "square.h"

#include "circle.h"
#include "point.h"

namespace bulumutka {

namespace {

constexpr double SQUARE_COEF = 1.0;

} // namespace

Square::Square(
    const Point& start,
    const Point& end
) : Rectangle(start, end, SQUARE_COEF) {}

// Rectangle
Circle Square::circumscribedCircle() const {

}

Circle Square::inscribedCircle() const {

}

// Polygon
bool Square::operator==(const Shape& other) const {

}

}
