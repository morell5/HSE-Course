#include "point.h"
#include "constants.h"
#include <cmath>


bool operator==(const Point& lhs, const Point& rhs) {
    return fabs(lhs.x - rhs.x) < GeometryConstants::EPS && fabs(lhs.y - rhs.y) < GeometryConstants::EPS;
}

bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

Point operator+(const Point& lhs, const Point& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Point operator-(const Point& lhs, const Point& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

Point operator*(const Point& point, double multiplier) {
    return {point.x * multiplier, point.y * multiplier};
}

