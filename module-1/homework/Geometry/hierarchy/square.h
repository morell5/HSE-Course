#pragma once
#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

#include "circle.h"

class Square : public Rectangle {
public:
	Point first_point, second_point;
	Square();
	Square(Point first, Point second);
	~Square() = default;
	Circle circumscribedCircle();
	Circle inscribedCircle();
};

#endif  // !SQUARE_H
