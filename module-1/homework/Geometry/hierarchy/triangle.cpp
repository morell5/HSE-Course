#include "triangle.h"

#include "circle.h"
#include "point.h"

#include <vector>

namespace bulumutka {

Triangle::Triangle(
    const Point& first,
    const Point& second, 
    const Point& third
) : Polygon({ first, second, third }) {}

// Rectangle
Circle Triangle::circumscribedCircle() const {

}

Circle Triangle::inscribedCircle() const {

}

// Polygon
bool Triangle::operator==(const Shape& other) const {

}

}
