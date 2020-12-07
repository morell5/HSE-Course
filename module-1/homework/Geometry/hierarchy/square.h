#pragma once
#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"
<<<<<<< HEAD

#include "circle.h"

class Square : public Rectangle {
=======
#include "circle.h"

class Square : public Rectangle
{
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
public:
	Point first_point, second_point;
	Square();
	Square(Point first, Point second);
<<<<<<< HEAD
	~Square() = default;
=======
	~Square();
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
	Circle circumscribedCircle();
	Circle inscribedCircle();
};

<<<<<<< HEAD
#endif  // !SQUARE_H
=======
#endif // !SQUARE_H



>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
