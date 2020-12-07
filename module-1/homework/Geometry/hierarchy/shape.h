#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include "line.h"

<<<<<<< HEAD
class Shape {
public:
	void out();
	std::vector<Point> vertices;
	const bool operator==(const Shape& another);
=======
class Shape
{
public:
	std::vector<Point> vertices;
	const bool operator == (const Shape& another);
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
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

<<<<<<< HEAD
#endif  // !SHAPE_H
=======
#endif // !SHAPE_H

>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
