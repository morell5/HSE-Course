#ifndef POINT_H_
#define POINT_H_

namespace bulumutka {

struct Point {
    Point(double x, double y);

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    const double x;
    const double y;
};

}

#endif
