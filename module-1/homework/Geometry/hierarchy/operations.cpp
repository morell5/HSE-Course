#include "operations.h"

double PointOperations::dotProduct(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double PointOperations::crossProduct(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

double PointOperations::hypot(const Point& lhs, const Point& rhs) {
    return sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y));
}

double PointOperations::hypot(const Point& point) {
    return hypot(point, {});
}

Point PointOperations::norm(const Point& point) {
    double hypot_ = hypot(point);
    return {point.x / hypot_, point.y / hypot_};
}

