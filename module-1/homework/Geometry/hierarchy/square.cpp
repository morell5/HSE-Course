#include "square.h"

double lenght(const Point first, const Point second) {
    return sqrt((first.x - second.x) * (first.x - second.x) +
        (first.y - second.y) * (first.y - second.y));
}

const double side_square(const Point first, const Point second) {
    double len = (first.x - second.x) * (first.x - second.x) +
        (first.y - second.y) * (first.y - second.y) / 2.0;
    return sqrt(len);
}

Square::Square() {
    this->first_point = Point(0, 0);
    this->second_point = Point(0, 0);
}

Square::Square(const Point first, const Point second) {
    this->first_point = first;
    this->second_point = second;
}

Circle Square::circumscribedCircle() {
    double rad = lenght(this->first_point, this->second_point) / 2.0;
    Point center((this->first_point.x + this->second_point.x) / 2.0,
        (this->first_point.y + this->second_point.y) / 2.0);
    Circle result(rad, center);
    return result;
}

Circle Square::inscribedCircle() {
    double rad = side_square(this->first_point, this->second_point) / 2.0;
    Point center((this->first_point.x + this->second_point.x) / 2.0,
        (this->first_point.y + this->second_point.y) / 2.0);
    Circle result(rad, center);
    return result;
}
