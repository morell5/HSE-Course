#pragma once
#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line
{
private:
	Point delta(const Point& first, const Point& second);
public:
	Point first_point, second_point;
	Line();
	Line(Point first_point, Point second_point);
	const bool operator == (const Line& new_line);
	const bool operator != (const Line& new_line);
};

#endif 

