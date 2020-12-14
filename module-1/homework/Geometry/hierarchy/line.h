#pragma once
#include "point.h"

class Line{
    public:

        Line(const Point& a1, const Point& a2);

        Point a1;
        Point a2;

        bool operator==(const Line& p) const;
        bool operator!=(const Line& p) const;
        
        Point getProjection(const Point& point) const;

};
