#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
const double pi = 3.1415926;

class Point{

    public:
        double x = 0;
        double y = 0;
        
        Point(double a, double b);
        Point();

        Point& operator=(const Point& a);
        bool operator==(const Point& a) const;
        bool operator!=(const Point& a) const;
        Point operator+(const Point& a) const;
        Point operator-(const Point& a) const;
        Point operator*(const double& a) const;
        Point operator/(const double& a) const;
        Point& operator+=(const Point& a);
        Point abc() const;
};

class Vector{
    public:
    double x = 0, y = 0;

    Vector();
    Vector(const Point& a, const Point& b);
    
    friend bool isConvexv(const Vector& a, const Vector& b);

    double lengh();

};

