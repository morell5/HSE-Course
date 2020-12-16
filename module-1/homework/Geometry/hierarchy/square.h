#pragma once
#include "rectangle.h"

class Square : public Rectangle{
    public:
    Square();
    Square(const Point& p1, const Point& p2);

    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
};