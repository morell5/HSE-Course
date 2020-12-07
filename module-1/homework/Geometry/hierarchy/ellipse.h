<<<<<<< HEAD

=======
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
#pragma once
#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "line.h"
<<<<<<< HEAD

#include <cmath>

class Ellipse {
private:
	double a, b, c, e;
	Point ellipse_center;

=======
#include <cmath>

class Ellipse
{
private:
	double a, b, c, e;
	Point ellipse_center;
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
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
<<<<<<< HEAD
	double area();
	bool containsPoint(const Point& point);
	Point center();
};

#endif  // !ELLIPSE_H
=======
	double area(); 
	bool containsPoint(const Point &point);
	Point center();
};

#endif // !ELLIPSE_H

>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
