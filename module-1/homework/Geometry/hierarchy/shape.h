#pragma once
#include "line.h"

class Shape {

public:

	virtual ~Shape() {}

	virtual double perimeter() const = 0;
	virtual double area() const = 0;
	virtual bool operator==(const Shape& another) const = 0;
	virtual bool isCongruentTo(const Shape& another) const = 0;
	virtual bool isSimilarTo(const Shape& another) const = 0;
	virtual bool containsPoint(const Point& point) const = 0;
	virtual Shape& rotate(const Point& center, const double& angle) = 0;
	virtual Shape& reflex(const Point& center) = 0;
	virtual Shape& reflex(const Line& axis) = 0;
	virtual Shape& scale(const Point& center, const double& coefficient) = 0;

};