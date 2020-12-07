<<<<<<< HEAD

=======
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
#include "line.h"

Line::Line() {};

<<<<<<< HEAD
Line::Line(Point first_point, Point second_point) {
    this->first_point = first_point;
    this->second_point = second_point;
}

Point Line::delta(const Point& first, const Point& second) {
    return Point(fabs(first.x - second.x), fabs(first.y - second.y));
}

const bool Line::operator==(const Line& new_line) {
    Point delta_1 = delta(this->first_point, this->second_point);
    Point delta_2 = delta(this->first_point, *&(new_line.first_point));
    Point delta_3 = delta(this->first_point, *&(new_line.second_point));
    bool first_cond = (delta_1.x * delta_2.y == delta_1.y * delta_2.x);
    bool second_cond = (delta_1.x * delta_3.y == delta_1.y * delta_3.x);
    if (first_cond && second_cond) {
        return true;
    }
    return false;
}

const bool Line::operator!=(const Line& new_line) {
    if (this == &new_line) {
        return false;
    }
    return true;
}

=======
Line::Line(Point first_point, Point second_point)
{
	this->first_point = first_point;
	this->second_point = second_point;
}

Point Line::delta(const Point& first, const Point& second)
{
	return Point(fabs(first.x - second.x), fabs(first.y - second.y));
}

const bool Line::operator == (const Line& new_line)
{
	Point delta_1 = delta(this->first_point, this->second_point);
	Point delta_2 = delta(this->first_point, *&(new_line.first_point));
	Point delta_3 = delta(this->first_point, *&(new_line.second_point));
	if (delta_1.x * delta_2.y == delta_1.y * delta_2.x && delta_1.x * delta_3.y == delta_1.y * delta_3.x)
	{
		return true;
	}
	return false;
}

const bool Line::operator != (const Line& new_line)
{
	if (this == &new_line)
	{
		return false;
	}
	return true;
}


>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
