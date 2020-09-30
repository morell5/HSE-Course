#ifndef GEOMETRY_HIERARCHY_OPERATIONS_H_
#define GEOMETRY_HIERARCHY_OPERATIONS_H_

#include "point.h"
#include <cmath>

struct PointOperations {
    static double dotProduct(const Point& lhs, const Point& rhs);

    static double crossProduct(const Point& lhs, const Point& rhs);

    static double hypot(const Point& lhs, const Point& rhs);

    static double hypot(const Point& point);

    static Point norm(const Point& point);
};

#endif //GEOMETRY_HIERARCHY_OPERATIONS_H_
