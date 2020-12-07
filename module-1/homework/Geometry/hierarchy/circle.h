
#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H

#include "ellipse.h"

class Circle : public Ellipse {
public:
	Circle();
	Circle(double rad, Point cir_center);
	double rad;
	Point cir_center;
	double radius();
};
#endif  // !CIRCLE_H
