#ifndef GEOMETRY_HIERARCHY_SHAPE_H_
#define GEOMETRY_HIERARCHY_SHAPE_H_

#include "line.h"


class Shape {
public:
    virtual double perimeter() const = 0;

    virtual double area() const = 0;

    virtual bool operator==(const Shape& another) const = 0;

    virtual bool isCongruentTo(const Shape& another) const = 0;

    //Подобие
    virtual bool isSimilarTo(const Shape& another) const = 0;

    virtual bool containsPoint(const Point& point) const = 0;

    //angle - градусы
    virtual void rotate(const Point& center, double angle) = 0;

    virtual void reflex(const Point& center) = 0;

    virtual void reflex(const Line& axis) = 0;

    virtual void scale(const Point& center, double scale) = 0;
};


#endif //GEOMETRY_HIERARCHY_SHAPE_H_