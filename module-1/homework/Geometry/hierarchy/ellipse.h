#pragma once
#include "shape.h"

class Ellipse : public Shape {
    public:

    Ellipse(const Point& f1, const Point& f2, const double& rad);

    Point f1, f2;
    double rade;

    std::pair<Point,Point> focuses() const;// - фокусы эллипса
    std::pair<Line, Line> directrices() const;// - пара директрис эллипса
    double eccentricity() const;// - эксцентриситет
    Point center() const;

   double perimeter() const override;
   double area() const override;
   bool operator==(const Shape& another) const override;
   bool isCongruentTo(const Shape& another) const override;
   bool isSimilarTo(const Shape& another) const override;
   bool containsPoint(const Point& point) const override;
   Shape& rotate(const Point& center, const double& angle) override;
   Shape& reflex(const Point& center) override;
   Shape& reflex(const Line& axis) override;
   Shape& scale(const Point& center, const double& coefficient) override;
   double cc() const;
   double bb() const;
   double aa() const;


   protected:
    double a = rade/2;
    double c = Vector(f1,f2).lengh() / 2;
    double b = sqrt(a*a - c*c);
    double e = c/a;
};