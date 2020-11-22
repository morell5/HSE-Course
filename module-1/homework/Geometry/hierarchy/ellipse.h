#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include "shape.h"

#include <utility>

namespace bulumutka {

class Line;
class Point;

class Ellipse : public Shape {
public:
    Ellipse(const Point& first, const Point& second, double dist);

    virtual ~Ellipse() override {};

    // Ellipse
    virtual std::pair<Point,Point> focuses() const;
    virtual std::pair<Line, Line> directrices() const;
    virtual double eccentricity() const;
    virtual Point center() const;

    // Shape
    virtual double perimeter() const override;
    virtual double area() const override;
    virtual bool operator==(const Shape& other) const override;
    virtual bool isCongruentTo(const Shape& other) const override;
    virtual bool isSimilarTo(const Shape& other) const override;
    virtual bool containsPoint(const Point& point) const override;

    virtual void rotate(const Point& center, double angle) override;
    virtual void reflex(const Point& center) override;
    virtual void reflex(const Line& axis) override;
    virtual void scale(const Point& center, double coef) override;

private:
    Point first_;
    Point second_;
    double dist_;
};

}

#endif
