#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"
#include "circle.h"
#include "point.h"

class Triangle : public Polygon
{
private:
	Vector vec[3];
public:
	Triangle();
	Triangle(Point& a, Point& b, Point& c);
	Circle circumscribedCircle();
	Circle inscribedCircle();
};


#endif // !TRIANGLE_H

