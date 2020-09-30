#ifndef GEOMETRY_HIERARCHY_TRIANGLE_H_
#define GEOMETRY_HIERARCHY_TRIANGLE_H_

#include "circle.h"
#include "polygon.h"


class Triangle: public Polygon {
private:
    static Point intersectLines(const Line&, const Line&);
public:
    Triangle(const Point& a, const Point& b, const Point& c);

    Circle circumscribedCircle() const;

    Circle inscribedCircle() const;
};

#endif //GEOMETRY_HIERARCHY_TRIANGLE_H_