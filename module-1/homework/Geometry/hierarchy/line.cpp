#include "line.h"

#include "point.h"

namespace bulumutka {

Line::Line(const Point& start, const Point& end)
    : start(start), end(end) {}

bool Line::operator==(const Line& other) const {
    return (start == other.start && end == other.end)
        || (start == other.end && end == other.start);
}

}
