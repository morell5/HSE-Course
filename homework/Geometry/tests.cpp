#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

#include "hierarchy/polygon.h"
#include "hierarchy/point.h"
#include "hierarchy/line.h"
#include "hierarchy/rectangle.h"
#include "hierarchy/triangle.h"
#include "hierarchy/circle.h"
#include "hierarchy/ellipse.h"
#include "hierarchy/square.h"

#include "gtest/gtest.h"

double dist(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y-b.y));
}

TEST(PointsDistance, TestOne) {
    Point a(3, 0);
    Point b(0, 4);

    ASSERT_NEAR(dist(a, b), 5.0, 6);
}

TEST(Polygon, EqualOperator) {
    Point a(1, 1);
    Point b(-1, 1);
    Point c(-1, -1);
    Point d(1, -1);

    std::vector<Point> vec = {a, b, c, d};
    Polygon actual(vec);
    vec = {d, a, b, c};
    Polygon expected(vec);
    ASSERT_TRUE(actual == expected);
}

TEST(Polygon, PolygonConvexity) {
    Point a(0, 1);
    Point b(-1, 0);
    Point c(0, -1);
    Point d(1, 0);

    std::vector<Point> vec = {a, b, c, d};
    Polygon poly(vec);
    ASSERT_TRUE(poly.isConvex());
}

TEST(Similarity, Test1) {
    std::vector<Point> vec;
    {
        Point a(0, 1);
        Point b(-1, 0);
        Point c(0, -1);
        Point d(1, 0);
        vec = {a, b, c, d};
    }
    
    Polygon actual(vec);

    {
        Point a(20, 20);
        Point b(-20, 20);
        Point c(-20, -20);
        Point d(20, -20);
        vec = {a, b, c, d};
    }

    Polygon expected(vec);

    ASSERT_TRUE(actual.isSimilarTo(expected));
}

TEST(Similarity, Test2) {
    std::vector<Point> vec;
    {
        Point a(0, 1);
        Point b(-1, 0);
        Point c(0, -1);
        Point d(1, 0);
        vec = {a, b, c, d};
    }
    
    Polygon actual(vec);

    {
        Point a(11, 11);
        Point b(-11, -11);
        Point c(0, -100);
        vec = {a, b, c};
    }

    Polygon expected(vec);

    ASSERT_FALSE(actual.isSimilarTo(expected));
}

TEST(Congruent, Congruent) {
    std::vector<Point> vec;
    {
        Point a(0, 1);
        Point b(-1, 0);
        Point c(0, -1);
        Point d(1, 0);
        vec = {a, b, c, d};
    }
    
    Polygon actual(vec);

    actual.rotate({0, 0}, 45);
    actual.scale({0, 0}, sqrt(2));
    {
        Point a(1, 1);
        Point b(-1, 1);
        Point c(-1, -1);
        Point d(1, -1);
        vec = {a, b, c, d};
    }
    

    Polygon expected(vec);

    ASSERT_TRUE(actual.isCongruentTo(expected));
}

TEST(Area, TrianglePolygons) {
    Point a(1.0, 0.0);
    Point b(0.0, 1.0);
    Point c(2.0, 1.0);
    Point d(1, 1.5);

    Triangle triangle1(a, b, d);
    Triangle triangle2(a, c, d);

    std::vector<Point> vec = {a, b, d, c};
    Polygon poly(vec);
    
    ASSERT_NEAR(poly.area(), triangle1.area() + triangle2.area(),1e-6);
}

TEST(Transformations, Test1) {
    std::vector<Point> vec;
    {
        Point a(1, 1);
        Point b(-1, 1);
        Point c(-1, -1);
        Point d(1, -1);

        vec = {a, b, c, d};
    }
  
    Polygon actual(vec);
    actual.rotate(Point(0,0), 45);
    actual.scale(Point(0,0), 20);
    actual.scale(Point(0,0), 1 / sqrt(2));
    {
        Point a(0, 20);
        Point b(-20, 0);
        Point c(0, -20);
        Point d(20, 0);

        vec = {a, b, c, d};
    }
  
    Polygon expected(vec);

    ASSERT_TRUE(actual == expected);
    ASSERT_NEAR(actual.perimeter(), expected.perimeter(),1e-6);
    ASSERT_NEAR(actual.area(), expected.area(),1e-6);
}

TEST(Transformations, Test2) {
    Point a(0, 0);
    Point b(-1, -1);
    Point c(1, -1);
    Point d(-1, 1);
    Point e(1, 1);

    Triangle actual(a, b, c);
    Triangle expected(a, d, e);
    actual.rotate(a, 45);
    actual.scale(a, 20);
    actual.rotate(a , 45);
    Line line(a, {1, 1});
    actual.reflex(line);
    actual.scale(a, 0.05);   

    ASSERT_TRUE(actual == expected);
}

TEST(Rectangle, Test1) {
    Point a(1.0, 0.0);
    Point b(2.5, 3.0);
    Point c(1.0, 3.0);
    double ratio = 0.5;
    
    Rectangle rectangle(a, b, ratio);
    Triangle triangle(a, b, c);
    ASSERT_NEAR(rectangle.area(), 2 * triangle.area(), 1e-6);
}

TEST(ContainsPoint, Test1) {
    Point a(1.0, 0.0);
    Point b(2.5, 3.0);
    Point c(1.0, 3.0);
    Point d(2.5, 0.0);

    std::vector<Point> vec = {a, b, c, d};
    Polygon poly(vec);

    ASSERT_TRUE(poly.containsPoint(Point(1.5, 1)));
}

TEST(ContainsPoint, Test2) {
    Point a(-1.0, 0.0);
    Point b(1.0, 0.0);

    Ellipse ellipse(a, b, 4);
    ASSERT_TRUE(ellipse.containsPoint(Point(0, 0)));
}

TEST(Ellipse, Eccentricity) {
    Point a(-1.0, 0.0);
    Point b(1.0, 0.0);
    Ellipse ellipse(a, b, 4);

    double eccentricity = 0.5;
    ASSERT_NEAR(ellipse.eccentricity(), eccentricity, 1e-6);
}

TEST(Ellipse, Perimeter) {
    double a = 5;
    double b = 4;
    double c = 3;

    Point p1(-c, 0.0);
    Point p2(c, 0.0);
    Ellipse ellipse(p1, p2, 2 * a);
    double pi = 3.1415926;

    double perimeter = 4 * (pi * a * b + (a - b)) / (a + b);
    ASSERT_NEAR(ellipse.perimeter(), perimeter, 1e-6);
}

TEST(Ellipse, Area) {
    double a = 5;
    double b = 4;
    double c = 3;

    Point p1(-c, 0.0);
    Point p2(c, 0.0);
    Ellipse ellipse(p1, p2, 2 * a);
    double pi = 3.1415926;
    
    double area = pi * a * b;
    ASSERT_NEAR(ellipse.area(), area, 1e-6);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}