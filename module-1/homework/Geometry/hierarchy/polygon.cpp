#include "polygon.h"

#include "line.h"
#include "point.h"

namespace bulumutka {

Polygon::Polygon(const std::vector<Point>& vertices)
    : vertices_(vertices) {}

// Polygon
int Polygon::verticesCount() const {
    return vertices_.size();
}

std::vector<Point> Polygon::getVertices() const {
    return vertices_;
}

bool Polygon::isCovex() const {
    
}

// Shape
double Polygon::perimeter() const {

}

double Polygon::area() const {

}

bool Polygon::operator==(const Shape& other) const {

}

bool Polygon::isCongruentTo(const Shape& other) const {

}

bool Polygon::isSimilarTo(const Shape& other) const {

}

bool Polygon::containsPoint(const Point& point) const {

}

void Polygon::rotate(const Point& center, double angle) {

}

void Polygon::reflex(const Point& center) {

}

void Polygon::reflex(const Line& axis) {

}

void Polygon::scale(const Point& center, double coef) {

}

}
