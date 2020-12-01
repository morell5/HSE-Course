#include "line.h"

Line::Line() {};

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


