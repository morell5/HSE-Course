#include "line.h"

Line::Line(const Point& x, const Point& y){
	a1 = x;
	a2 = y;
}

bool Line::operator==(const Line& p) const{
    return ((this->a1-this->a2).abc() == (p.a1 - p.a2).abc());
}

bool Line::operator!=(const Line& p) const{
    return (!((this->a1-this->a2).abc() == (p.a1 - p.a2).abc()));
}

Point Line::getProjection(const Point& point) const {
	double m = a1.x - a2.x, p = a1.y - a2.y;
	double x = a1.x, y = a1.y;
	double t = (m * point.x + p * point.y - m * x - p * y) / (m*m + p*p);

	return Point(m * t + x, p * t + y);
}
