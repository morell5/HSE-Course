#ifndef GEOMETRY_HIERARCHY_POINT_H_
#define GEOMETRY_HIERARCHY_POINT_H_

struct Point {
    double x;
    double y;

    Point(): x(0), y(0) {}

    Point(double x, double y): x(x), y(y) {}

    friend bool operator==(const Point&, const Point&);
    friend bool operator!=(const Point&, const Point&);

    friend Point operator+(const Point&, const Point&);
    friend Point operator-(const Point&, const Point&);

    friend Point operator*(const Point&, double);
};

#endif //GEOMETRY_HIERARCHY_POINT_H_