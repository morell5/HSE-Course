#pragma once
#ifndef POLYGON_H
#define POLYGON_H

#include "line.h"
<<<<<<< HEAD

#include <vector>

#include "shape.h"

class Polygon : public Shape {
=======
#include <vector>
#include "shape.h"

class Polygon : public Shape
{
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
public:
	bool isConvex();
	std::vector<Point> getVertices();
	int verticesCount();
	Polygon();
<<<<<<< HEAD
	Polygon(const std::vector<Point>& a);
	~Polygon() = default;
};

#endif  // !POLYGON_H
=======
	Polygon(const std::vector<Point> &a);
	~Polygon() = default;
};

#endif // !POLYGON_H

>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
