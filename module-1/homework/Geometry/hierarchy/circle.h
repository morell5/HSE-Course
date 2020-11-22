#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "ellipse.h"

namespace bulumutka {

class Point;

class Circle : public Ellipse {
public:
    Circle(const Point& center, double radius);
    virtual ~Circle() override {};

    // Circle
    virtual double radius() const;

    // Shape
    virtual bool operator==(const Shape& other) const override;
};

}

#endif
