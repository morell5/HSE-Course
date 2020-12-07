#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygon.h"

class Rectangle : public Polygon {
public:
	double k;
	Point center();
	Rectangle();
	Rectangle(Point a, Point b, double& ratio);
	std::pair<Line, Line> diagonals();
};

#endif  // !1
