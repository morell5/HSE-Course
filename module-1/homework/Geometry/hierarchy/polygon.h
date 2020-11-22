#ifndef POLYGON_H_
#define POLYGON_H_

#include "shape.h"

#include <vector>

namespace bulumutka {

class Line;
class Point;

class Polygon : public Shape {
public:
    Polygon(const std::vector<Point>& vertices);

    virtual ~Polygon() override {};

    // Polygon
    virtual int verticesCount() const;
    virtual std::vector<Point> getVertices() const;
    virtual bool isCovex() const;

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
    std::vector<Point> vertices_;
};

}

#endif
