#include "ellipse.h"

#include "line.h"
#include "point.h"

namespace bulumutka {

Ellipse::Ellipse(
    const Point& first,
    const Point& second,
    double dist
) : first_(first), second_(second), dist_(dist) {}

// Ellipse
std::pair<Point,Point> Ellipse::focuses() const {

}

std::pair<Line, Line> Ellipse::directrices() const {

}

double Ellipse::eccentricity() const {

}

Point Ellipse::center() const {

}

// Shape
double Ellipse::perimeter() const {

}

double Ellipse::area() const {

}

bool Ellipse::operator==(const Shape& other) const {

}

bool Ellipse::isCongruentTo(const Shape& other) const {

}

bool Ellipse::isSimilarTo(const Shape& other) const {

}

bool Ellipse::containsPoint(const Point& point) const {

}

void Ellipse::rotate(const Point& center, double angle) {

}

void Ellipse::reflex(const Point& center) {

}

void Ellipse::reflex(const Line& axis) {

}

void Ellipse::scale(const Point& center, double coef) {

}

}
