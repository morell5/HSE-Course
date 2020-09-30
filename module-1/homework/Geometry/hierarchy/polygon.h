#ifndef GEOMETRY_HIERARCHY_POLYGON_H_
#define GEOMETRY_HIERARCHY_POLYGON_H_

#include "shape.h"
#include <vector>


class Polygon: public Shape {
    std::pair<std::vector<double>, std::vector<double>> getLengthAndAngles() const;

protected:

    std::vector<Point> vertices_;
public:

    Polygon(): vertices_({}) {}

    Polygon(const std::vector<Point>& vertices): vertices_(vertices) {}

    int verticesCount() const;

    std::vector<Point> getVertices() const;

    bool isConvex() const;

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

#endif //GEOMETRY_HIERARCHY_POLYGON_H_