#ifndef GEOMETRY_HIERARCHY_ELLIPSE_H_
#define GEOMETRY_HIERARCHY_ELLIPSE_H_

#include <utility>
#include "shape.h"

class Ellipse: public Shape {
    Point foci_a_;
    Point foci_b_;
    double a_;
public:
    Ellipse(const Point& a, const Point& b, double dist_sum);

    std::pair<Point,Point> focuses() const;

    double getC() const;

    double eccentricity() const;

    Point center() const;

    double perimeter() const override;

    double area() const override;

    bool operator==(const Shape& another) const override;

    bool isCongruentTo(const Shape& another) const override;

    bool isSimilarTo(const Shape& another) const override;

    bool containsPoint(const Point& point) const override;

    void rotate(const Point& center, double angle) override;

    void reflex(const Point& center) override;

    void reflex(const Line& axis) override;

    void scale(const Point& center, double scale) override;
};

#endif //GEOMETRY_HIERARCHY_ELLIPSE_H_