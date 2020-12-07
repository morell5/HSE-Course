#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"
<<<<<<< HEAD

#include "circle.h"

#include "point.h"

class Triangle : public Polygon {
private:
	Vector vec[3];

=======
#include "circle.h"
#include "point.h"

class Triangle : public Polygon
{
private:
	Vector vec[3];
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
public:
	Triangle();
	Triangle(Point& a, Point& b, Point& c);
	Circle circumscribedCircle();
	Circle inscribedCircle();
};

<<<<<<< HEAD
#endif  // !TRIANGLE_H
=======

#endif // !TRIANGLE_H

>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
