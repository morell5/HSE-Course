#include "ellipse.h"
#include <cmath>

double pi = 3.1415926;

Ellipse::Ellipse() {
	this->a = 0;
	this->b = 0;
	this->c = 0;
	this->e = 0;
	this->F1 = Point(0, 0);
	this->F2 = Point(0, 0);
	this->sum_r = 0;
}

Ellipse::Ellipse(Point F1, Point F2, double sum_r) {
	this->F1 = F2;
	this->F2 = F2;
	this->sum_r = sum_r;
	this->a = sum_r / 2;
	this->c = std::max(F1.x, F2.x) - (F1.x + F2.x) / 2.0;
	this->b = std::sqrt(this->a * this->a - this->c * this->c);
	this->ellipse_center = Point((F1.x + F2.x) / 2.0, F1.y);
	this->e = this->c / this->a;
}

std::pair<Point, Point> Ellipse::focuses() {
	std::pair<Point, Point> result;
	result = std::make_pair(this->F1, this->F2);
	return result;
}

std::pair<Line, Line> Ellipse::directrices() {
	return std::make_pair(Line(Point(-a / e, 0), Point(-a / e, 1)), Line(Point(a / e, 0), Point(a / e, 1)));
}

double Ellipse::eccentricity() {
	return this->e;
}

Point Ellipse::center() {
	return this->ellipse_center;
}

double Ellipse::perimeter() {
	return 4 * (pi * a * b + (a - b)) / (a + b);
}

double Ellipse::area() {
	return pi * (this->a * this->b);
}

bool Ellipse::containsPoint(const Point& point) {
	if (point.x * point.x / (this->a * this->a) + point.y * point.y / (this->b * this->b) <= 1) {
		return true;
	}
	return false;
}
