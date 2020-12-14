#include "rectangle.h"


Rectangle::Rectangle(const Point& a1, const Point& a2, const double& otn) : Polygon({}){
    getVertices.push_back(a1);
    Point a3 = a1, a4 = a1;
    Vector b1(a2, a1), b2(a2, a1);
    b1.x = 0;
    b2.y = 0;
    a3.x += b2.x;
    a4.y += b1.y;
    getVertices.push_back(a3);
    getVertices.push_back(a2);
    getVertices.push_back(a4);
}

Point Rectangle::center() const{
    return((getVertices[0] + getVertices[2])/2);
}

std::pair<Line, Line> Rectangle::diagonals() const{
    return (std::pair<Line, Line>(Line(getVertices[0], getVertices[2]), Line(getVertices[1], getVertices[3])));
}