#include "square.h"

Square::Square(const Point& p1, const Point& p2) {
    Rectangle(p1,p2,1); 
}

Circle Square::circumscribedCircle() const{
    return Circle((getVertices[0]+getVertices[2])/2, Vector(getVertices[0],getVertices[2]).lengh()/2);
}

Circle Square::inscribedCircle() const{
    return Circle((getVertices[0]+getVertices[2])/2, abs(getVertices[0].x-getVertices[2].x)/2);
}