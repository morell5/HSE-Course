#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygon.h"

<<<<<<< HEAD
class Rectangle : public Polygon {
=======
class Rectangle : public Polygon
{
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
public:
	double k;
	Point center();
	Rectangle();
	Rectangle(Point a, Point b, double& ratio);
	std::pair<Line, Line> diagonals();
};

<<<<<<< HEAD
#endif  // !1
=======
#endif // !1


>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
