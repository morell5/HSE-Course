#pragma once
#ifndef POINT_H
#define POINT_H

#include <iostream>

#include <cmath>

#include <vector>

#include <algorithm>

class Vector {
public:
    Vector();
    Vector(double x, double y, double vector_len)
        : x(x), y(y), vector_len(vector_len) {}
    double vector_len;
    double x, y;
    double len();
    const Vector operator*(const double value);
    ~Vector() = default;
};

class Point {
public:
    double x, y;
    const bool operator==(const Point& new_point);
    const bool operator!=(const Point& new_point);
    const void operator=(const Point& new_point);
    Point(double x, double y);
    Point(const Point& point);
    Point();
    ~Point() = default;
};

#endif
