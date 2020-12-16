#pragma once
#include "polygon.h"

class Triangle : public Polygon {
    public:
    Triangle(const Point& tch1, const Point& tch2, const Point& tch3);
    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
};