#include "circle.h"

Circle::Circle() {
	cir_center.x = 0;
	cir_center.y = 0;
	rad = 0;
}
Circle::Circle(double rad, Point cir_center) {
	this->cir_center = cir_center;
	this->rad = rad;
}
double Circle::radius() { return this->sum_r / 2.0; }
