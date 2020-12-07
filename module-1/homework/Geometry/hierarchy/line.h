<<<<<<< HEAD

=======
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
#pragma once
#ifndef LINE_H
#define LINE_H

#include "point.h"

<<<<<<< HEAD
class Line {
private:
	Point delta(const Point& first, const Point& second);

=======
class Line
{
private:
	Point delta(const Point& first, const Point& second);
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
public:
	Point first_point, second_point;
	Line();
	Line(Point first_point, Point second_point);
<<<<<<< HEAD
	const bool operator==(const Line& new_line);
	const bool operator!=(const Line& new_line);
};

#endif
=======
	const bool operator == (const Line& new_line);
	const bool operator != (const Line& new_line);
};

#endif 

>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
