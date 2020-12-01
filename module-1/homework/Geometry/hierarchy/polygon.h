#pragma once
#ifndef POLYGON_H
#define POLYGON_H

#include "line.h"
#include <vector>
#include "shape.h"

class Polygon : public Shape
{
public:
	bool isConvex();
	std::vector<Point> getVertices();
	int verticesCount();
	Polygon();
	Polygon(const std::vector<Point> &a);
	~Polygon() = default;
};

#endif // !POLYGON_H

