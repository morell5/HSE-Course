#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include "line.h"

class Shape {
public:
	void out();
	std::vector<Point> vertices;
	const bool operator==(const Shape& another);
	double perimeter();
	double area();
	bool isSimilarTo(const Shape& another);
	bool isCongruentTo(const Shape& another);
	void reflex(Point center);
	void reflex(Line axis);
	void scale(Point center, double coefficient);
	bool containsPoint(Point point);
	void rotate(Point center, double angle);
};

#endif  // !SHAPE_H
