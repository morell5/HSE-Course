#pragma once
#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "line.h"
#include <cmath>

class Ellipse
{
private:
	double a, b, c, e;
	Point ellipse_center;
public:
	Ellipse();
	Ellipse(Point F1, Point F2, double sum_lenght);
	Point F1;
	Point F2;
	double sum_r;
	std::pair<Point, Point> focuses();
	std::pair<Line, Line> directrices();
	double eccentricity();
	double perimeter();
	double area(); 
	bool containsPoint(const Point &point);
	Point center();
};

#endif // !ELLIPSE_H

