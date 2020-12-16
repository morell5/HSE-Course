#pragma once
#include "polygon.h"

class Rectangle : public Polygon{
    public:
    Rectangle();

    Rectangle(const Point& a1, const Point& a2, const double& otn);

    Point center() const;// - центр круга
    std::pair<Line, Line> diagonals() const;//- пара диагоналей
};