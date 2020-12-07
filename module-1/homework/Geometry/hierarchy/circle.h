<<<<<<< HEAD

=======
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
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
<<<<<<< HEAD
#endif  // !CIRCLE_H
=======
#endif // !CIRCLE_H

>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
