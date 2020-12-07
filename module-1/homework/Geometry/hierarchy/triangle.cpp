#include "triangle.h"

bool cmp(const Point& a, const Point& b) { return a.x < b.x; }
double vec_pr(const Vector& a, const Vector& b) {
    return a.x * b.y - a.y * b.x;
}
double leng(const Point first, const Point second) {
    return sqrt((first.x - second.x) * (first.x - second.x) +
        (first.y - second.y) * (first.y - second.y));
}
Triangle::Triangle() {
    Point p[3];
    for (int i = 0; i < 3; i++) {
        p[i] = this->vertices[i];
    }
    vec[0] = Vector(p[1].x - p[0].x, p[1].y - p[0].y, leng(p[0], p[1]));
    vec[1] = Vector(p[2].x - p[0].x, p[2].y - p[0].y, leng(p[0], p[2]));
    vec[2] = Vector(p[2].x - p[1].x, p[2].y - p[1].y, leng(p[1], p[2]));
}
Triangle::Triangle(Point& a, Point& b, Point& c) {
    std::vector<Point> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    std::sort(v.begin(), v.end(), cmp);
    this->vertices.push_back(v[0]);
    if (v[0].y > v[1].y && v[1].y > v[2].y ||
        v[0].y < v[1].y && v[1].y > v[2].y) {
        this->vertices.push_back(v[2]);
        this->vertices.push_back(v[1]);
    }
    else {
        this->vertices.push_back(v[1]);
        this->vertices.push_back(v[2]);
    }
}
Circle Triangle::circumscribedCircle() {
    double sin_a =
        fabs(vec_pr(vec[0], vec[1])) / (vec[0].vector_len * vec[1].vector_len);
    double rad = this->vec[2].vector_len / sin_a / 2.0;
    Point p[4];
    for (int i = 0; i < 3; i++) {
        p[i + 1] = this->vertices[i];
    }
    double a1 = p[1].x * p[1].x - p[2].x * p[2].x;
    double y1 = p[1].x - p[2].x;
    double b1 = p[1].y * p[1].y - p[2].y * p[2].y;
    double q1 = p[1].y - p[2].y;

    double a2 = p[1].x * p[1].x - p[3].x * p[3].x;
    double y2 = p[1].x - p[3].x;
    double b2 = p[1].y * p[1].y - p[3].y * p[3].y;
    double q2 = p[1].y - p[3].y;

    double x0 = (a2 + b2 - (a1 + b1) * q2 / q1) / (2 * (y2 - (y1 / q1)));
    double y0 = (a1 - 2 * x0 * y1 + b1) / (2 * q1);
    Circle result;
    result.rad = rad;
    result.cir_center.x = x0;
    result.cir_center.y = y0;
    return result;
}
double area_t(Point& a, Point& b, Point& c) {
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) / 2.0;
}
Point middle_point(Point& a, Point& b) {
    return Point((a.x + b.x) / 2.0, (a.y + b.y) / 2.0);
}
double angle_side(Point& a, Point& b) { return (b.y - a.y) / (b.x - a.x); }
Circle Triangle::inscribedCircle() {
    Point p[3];
    for (int i = 0; i < 3; i++) {
        p[i].x = this->vertices[i].x;
        p[i].y = this->vertices[i].y;
    }
    double S = area_t(p[0], p[1], p[2]);
    double rad = S / (leng(p[0], p[1]) + leng(p[1], p[2]) + leng(p[2], p[0]));
    double x_c = (leng(p[0], p[1]) * p[2].x + leng(p[0], p[2]) * p[1].x +
        leng(p[1], p[2]) * p[0].x) /
        (leng(p[0], p[1]) + leng(p[0], p[2]) + leng(p[1], p[2]));
    double y_c = (leng(p[0], p[1]) * p[2].y + leng(p[0], p[2]) * p[1].y +
        leng(p[1], p[2]) * p[0].y) /
        (leng(p[0], p[1]) + leng(p[0], p[2]) + leng(p[1], p[2]));
    Circle res(rad, Point(x_c, y_c));
    return res;
}
