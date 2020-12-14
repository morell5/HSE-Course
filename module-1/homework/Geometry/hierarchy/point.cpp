#include "point.h"

Point::Point(){}

Point::Point(double a, double b){
    this->x = a;
    this->y = b;
}

Point& Point::operator=(const Point& a) {
    this->y = a.y;
    this->x = a.x;
    return *this;
}

bool Point::operator==(const Point& a) const{
    return ((this->x - a.x < 0.00001) && (this->x - a.x > -0.00001) && 
    (this->y - a.y < 0.00001) && (this->y - a.y > -0.00001));
}

bool Point::operator!=(const Point& a) const{
    return (!((this->x - a.x < 0.00001) && (this->x - a.x > -0.00001) && 
    (this->y - a.y < 0.00001) && (this->y - a.y > -0.00001)));
}

Point Point::operator-(const Point& a) const{
    Point b;
    b.x = this->x - a.x;
    b.y = this->y - a.y;
    return b;
}

Point Point::operator+(const Point& a) const{
    Point b;
    b.x = this->x + a.x;
    b.y = this->y + a.y;
    return b;
}

Point& Point::operator+=(const Point& a){
    this->x = this->x + a.x;
    this->y = this->y + a.y;
    return *this;
}

Point Point::operator*(const double& a) const{
    Point b;
    b.x = this->x * a;
    b.y = this->y * a;
    return b;
}

Point Point::operator/(const double& a) const{
    Point b;
    b.x = this->x / a;
    b.y = this->y / a;
    return b;
}

Point Point::abc() const{
    Point b = *this;
    if (b.x<0) b.x*=-1;
    if (b.y<0) b.y*=-1;
    return b;
}

Vector::Vector(){}

Vector::Vector(const Point& a, const Point& b){
        x = a.x - b.x;
        y = a.y - b.y;
    }

bool isConvexv(const Vector& a, const Vector& b){
    return (a.x*b.y-a.y*b.x > 0);
}

double Vector::lengh(){
    return(sqrt(x*x + y*y));
}