#include "point.h"

Vector::Vector() {
	this->x = 0;
	this->y = 0;
	this->vector_len = 0;
}

double Vector::len() {
	return sqrt(x * x + y * y);
}

const Vector Vector::operator * (const double value)  {
	Vector v;
	v.x = this->x * value;
	v.y = this->y * value;
	return v;
}
const void Point::operator = (const Point& new_point) {
	this->x = new_point.x;
	this->y = new_point.y;
}
const bool Point::operator ==(const Point& new_point) {
	if (this->x == new_point.x && this->y == new_point.y) {
		return true;
	}
	return false;
}
const bool Point::operator != (const Point& new_point) {
	if (*this == new_point) {
		return false;
	}
	return true;
}
Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}
Point::Point(const Point& new_point) {
	*this = new_point;
}
Point::Point() {
	this->x = -1e9;
	this->y = -1e9;
}
