#ifndef GEOMETRY_HIERARCHY_CIRCLE_H_
#define GEOMETRY_HIERARCHY_CIRCLE_H_

#include "ellipse.h"

class Circle: public Ellipse {
    double radius_;
public:
    Circle(const Point& center, double radius);
    double radius() const;
};


#endif //GEOMETRY_HIERARCHY_CIRCLE_H_