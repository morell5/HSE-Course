#include "ellipse.h"

Ellipse::Ellipse(const Point& a1, const Point& a2, const double& rad)
    : f1(a1), f2(a2), rade(rad) {}

std::pair<Point,Point> Ellipse::focuses() const{
    return (std::pair<Point, Point>(f1,f2));
}

std::pair<Line, Line> Ellipse::directrices() const{
    return(std::pair<Line, Line>(Line(Point(1, aa()/e), Point(2, aa()/e)), Line(Point(1, -aa()/e), Point(2, -aa()/e))));
}

double Ellipse::eccentricity() const{
    return e;
}

Point Ellipse::center() const{
    return((f1+f2)/2);
}

bool Ellipse::operator==(const Shape& another) const{
    const auto* another2 = dynamic_cast<const Ellipse*>(&another);
    bool ans = 0;
    if ((this->f1 == another2->f1) && (this->f2 == another2->f2) && (this->rade == another2->rade)){
        ans = 1;
    }
    return ans;
}

bool Ellipse::isCongruentTo(const Shape& another) const{
    const auto* another2 = dynamic_cast<const Ellipse*>(&another);
    bool ans = 0;
    if ((this->f1-this->f2 == another2->f1-another2->f2) && (this->rade == another2->rade)){
        ans = 1;
    }
    return ans;
}

bool Ellipse::isSimilarTo(const Shape& another) const{
    const auto* another2 = dynamic_cast<const Ellipse*>(&another);
    bool ans = 0;
    if (Vector(this->f1,this->f2).lengh() / Vector(another2->f1,another2->f2).lengh() 
    == this->rade / another2->rade){
        ans = 1;
    }
    return ans;   
}

bool Ellipse::containsPoint(const Point& another) const{
    bool convex = false;
    if (Vector(another, f1).lengh() + Vector(another, f2).lengh() <= rade) {
        convex = true;
    }
    return convex;
}

Shape& Ellipse::rotate(const Point& center, const double& angle){
    const auto* another2 = dynamic_cast<const Ellipse*>(this);
    double rad = angle * pi / 180.0;
    Vector g2;
    Vector g = Vector(f11(), center);
    g2.x = g.x*cos(rad) - g.y*sin(rad);
    g2.y = g.x*sin(rad) + g.y*cos(rad);
    f1.x+=g2.x;
    f1.y+=g2.y;
    g = Vector(f2, center);
    g2.x = g.x*cos(rad) - g.y*sin(rad);
    g2.y = g.x*sin(rad) + g.y*cos(rad);
    f2.x+=g2.x;
    f2.y+=g2.y;
    return *this;
}

Shape& Ellipse::reflex(const Point& center) {
    this->rotate(center, 180);
    return *this;
}

Shape& Ellipse::reflex(const Line& axis){
    Point proj = axis.getProjection(f1);
    f1 += (proj - f1) * 2;
    proj = axis.getProjection(f2);
    f2 += (proj - f2) * 2;
	return *this;
}

Shape& Ellipse::scale(const Point& center, const double& coefficient){
	f1 += (center - f1) * coefficient;
    f2 += (center - f2) * coefficient;
	return *this;
}

double Ellipse::perimeter() const {
    return 4 * (pi * aa() * bb() + (aa() - bb())) / (aa() + bb());
}

double Ellipse::cc() const {
    return Vector(f1,f2).lengh()/2;
}
double Ellipse::bb() const {
    return sqrt(aa()*aa() - cc()*cc());
}
double Ellipse::aa() const {
    return rade/2;
}

double Ellipse::area() const {
    return pi * aa() * bb();
}