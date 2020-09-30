#ifndef GEOMETRY_HIERARCHY_LINE_H_
#define GEOMETRY_HIERARCHY_LINE_H_

#include "point.h"

class Line {
    Point a_;
    Point b_;
public:
    Line(): a_({0, 0}), b_({0, 0}) {}
    Line(const Point& a, const Point& b): a_(a), b_(b) {}

    Point getFirstPoint() const;

    Point getSecondPoint() const;

    struct LineFormulaComponents {
        double x_coef;
        double y_coef;
        double c;
    };

    LineFormulaComponents getFormulaComponents() const;

    friend bool operator==(const Line& lhs, const Line& rhs);

    friend bool operator!=(const Line& lhs, const Line& rhs);
};

#endif //GEOMETRY_HIERARCHY_CONSTANTS_H_