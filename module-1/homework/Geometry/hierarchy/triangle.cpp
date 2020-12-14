#include "triangle.h"

Triangle::Triangle(const Point& tch1, const Point& tch2, const Point& tch3) : Polygon({}){
    getVertices = {tch1, tch2, tch3};
}

Circle Triangle::circumscribedCircle() const {
    double a = Vector(getVertices[0], getVertices[1]).lengh();
    double b = Vector(getVertices[1], getVertices[2]).lengh();
    double c = Vector(getVertices[2], getVertices[0]).lengh();
    double p = (a + b + c) / 2;
    double R = a * b * c / (4 * sqrt(p * (p - a) * (p - b) * (p - c)));

    int ang = -90;

    Vector g2;
    Vector g = Vector((getVertices[0] + getVertices[1]) / 2, getVertices[1]);
    g2.x = g.x*cos(ang) - g.y*sin(ang);
    g2.y = g.x*sin(ang) + g.y*cos(ang);
    Point center;
    center.x = getVertices[1].x + g2.x;
    center.x = getVertices[1].y + g2.y;
    center = (center * (R / Vector(center, getVertices[1]).lengh()));

    return Circle(center, R);
}

Circle Triangle::inscribedCircle() const {   
    double a = Vector(getVertices[0], getVertices[1]).lengh();
    double b = Vector(getVertices[1], getVertices[2]).lengh();
    double c = Vector(getVertices[2], getVertices[0]).lengh();
    double p = (a + b + c) / 2;
    double r = sqrt((p - a) * (p - b) * (p - c) / p);

    Vector gh1(getVertices[0], getVertices[1]);
    Vector gh2(getVertices[0], getVertices[2]);
    double ang = asin(sqrt(gh1.x * gh2.y - gh1.y * gh2.x) / (gh1.lengh() * gh2.lengh())) / 2;

    Vector g2;
    Vector g = Vector(getVertices[0], getVertices[1]);
    g2.x = g.x*cos(ang) - g.y*sin(ang);
    g2.y = g.x*sin(ang) + g.y*cos(ang);
    Point center;
    center.x = getVertices[1].x + g2.x;
    center.x = getVertices[1].y + g2.y;
    return Circle(center, r);
}