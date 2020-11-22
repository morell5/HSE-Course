#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "polygon.h"

namespace bulumutka {

class Circle;
class Point;

class Triangle : public Polygon{
public:
    Triangle(const Point& first, const Point& second, const Point& third);

    virtual ~Triangle() override {};

    // Square
    virtual Circle circumscribedCircle() const;
    virtual Circle inscribedCircle() const;

    // Square
    virtual bool operator==(const Shape& other) const override;
};

}

#endif
