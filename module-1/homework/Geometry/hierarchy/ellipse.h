#pragma once
#include "shape.h"

class Ellipse : public Shape {
    public:

    Ellipse(const Point& f1, const Point& f2, const double& rad);

    

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
   
   Point f11() {return f1;};
   Point f22() {return f2;};
   double ra_de() {return rade;};

   protected:
    Point f1, f2;
    double rade;
    double cc() const;
    double bb() const;
    double aa() const;
    double e = cc()/aa();
};