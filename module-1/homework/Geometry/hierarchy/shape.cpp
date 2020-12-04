#include "shape.h"

#include <vector>

#include <set>

const double pi = 3.1415926;

/*void Shape::out() {
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << vertices[i].x << ' ' << vertices[i].y << std::endl;
    }
    std::cout << std::endl;
}*/
// for vector
double operator*(const Vector& a, const Vector& b) {
    return a.x * b.y - a.y * b.x;
}
double operator%(const Vector& a, const Vector& b) {
    return a.x * b.x + a.y * b.y;
}
// for cross
bool is_on_line(Line line, Point p) {
    Point p2 = line.first_point;
    Point p3 = line.second_point;
    Vector v1(p.x - p2.x, p.y - p2.y, 0);
    Vector v2(p3.x - p2.x, p3.y - p2.y, 0);
    if (v1 * v2 != 0) return false;
    Vector v3(p.x - p3.x, p.y - p3.y, 0);
    Vector v4(p2.x - p3.x, p2.y - p3.y, 0);
    if (v3 % v4 >= 0 && v1 % v2 >= 0) return true;
    return false;
}
double area_t(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
bool is_crossed_1(double a, double b, double c, double d) {
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}
bool is_crossed(Point a, Point b, Point c, Point d) {
    return is_crossed_1(a.x, b.x, c.x, d.x) && is_crossed_1(a.y, b.y, c.y, d.y) &&
        area_t(a, b, c) * area_t(a, b, d) <= 0 &&
        area_t(c, d, a) * area_t(c, d, b) <= 0;
}
// containsPoint
bool Shape::containsPoint(Point point) {
    Point point_to(point.x + 2e9, point.y);
    int n = this->vertices.size();
    int counter = 0;
    for (int i = 0; i < n; i++) {
        int next_i = (i + 1) % n;
        if (is_on_line(Line(this->vertices[i], this->vertices[next_i]), point)) {
            return true;
        }
        if (is_crossed(point, point_to, this->vertices[i],
            this->vertices[next_i])) {
            counter++;
        }
        if (is_on_line(Line(point, point_to), this->vertices[i])) {
            int last_i = (i - 1 + n) % n;
            if (is_crossed(point, point_to, this->vertices[i],
                this->vertices[last_i])) {
                counter++;
            }
        }
    }
    if (counter % 2 == 1) {
        return true;
    }
    return false;
}
// len
const double len(Point first, Point second) {
    return sqrt((first.x - second.x) * (first.x - second.x) +
        (first.y - second.y) * (first.y - second.y));
}
//==
const bool Shape::operator==(const Shape& another) {
    if (this->vertices.size() != another.vertices.size()) {
        return false;
    }
    int n = this->vertices.size();
    double exp = 0.000001;
    std::vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        bool fi = false;
        for (int j = 0; j < n && !fi; j++) {
            double res_x = fabs(this->vertices[i].x - another.vertices[j].x);
            double res_y = fabs(this->vertices[i].y - another.vertices[j].y);
            if (!used[j] && res_x < exp && res_y < exp) {
                used[j] = true;
                fi = true;
            }
        }
        if (!fi) {
            return false;
        }
    }
    return true;
}
// perimetr
double Shape::perimeter() {
    double P = 0;
    int n = this->vertices.size();
    for (int i = 0; i < n; i++) {
        int next_i = (i + 1) % n;
        P += len(this->vertices[i], this->vertices[next_i]);
    }
    return P;
}
// area
double Shape::area() {
    int n = this->vertices.size();
    double S = 0;
    for (int i = 0; i < n; i++) {
        Point p1 = i ? this->vertices[i - 1] : this->vertices[n - 1];
        Point p2 = this->vertices[i];
        S += (p1.x - p2.x) * (p1.y + p2.y);
    }
    return fabs(S) / 2;
}
// isSimilarTo
bool Shape::isSimilarTo(const Shape& another) {
    std::vector<double> angle_this;
    std::vector<double> angle_another;
    int n = this->vertices.size();
    if (another.vertices.size() != n) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        int next_i = (i + 1) % n;
        int last_i = (i - 1 + n) % n;
        Vector v1(this->vertices[last_i].x - this->vertices[i].x,
            this->vertices[last_i].y - this->vertices[i].y, 0);
        Vector v2(this->vertices[next_i].x - this->vertices[i].x,
            this->vertices[next_i].y - this->vertices[i].y, 0);
        angle_this.push_back(std::fabs(v1 % v2 / (v1.len() * v2.len())));
    }
    for (int i = 0; i < n; i++) {
        int next_i = (i + 1) % n;
        int last_i = (i - 1 + n) % n;
        Vector v1(another.vertices[last_i].x - another.vertices[i].x,
            another.vertices[last_i].y - another.vertices[i].y, 0);
        Vector v2(another.vertices[next_i].x - another.vertices[i].x,
            another.vertices[next_i].y - another.vertices[i].y, 0);
        angle_another.push_back(std::fabs(v1 % v2 / (v1.len() * v2.len())));
    }
    for (int i = 0; i < n; i++) {
        bool can = true;
        for (int j = 0; j < n; j++) {
            if (angle_this[j] != angle_another[(j + i) % n]) {
                can = false;
                break;
            }
        }
        if (can) {
            return true;
        }
    }
    return false;
}
// isCongruentTo
bool Shape::isCongruentTo(const Shape& another) {
    std::vector<double> angle_this;
    std::vector<double> angle_another;
    int n = this->vertices.size();
    if (another.vertices.size() != n) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        int next_i = (i + 1) % n;
        int last_i = (i - 1 + n) % n;
        Vector v1(this->vertices[last_i].x - this->vertices[i].x,
            this->vertices[last_i].y - this->vertices[i].y, 0);
        Vector v2(this->vertices[next_i].x - this->vertices[i].x,
            this->vertices[next_i].y - this->vertices[i].y, 0);
        angle_this.push_back(std::fabs(v1 % v2 / (v1.len() * v2.len())));
    }
    for (int i = 0; i < n; i++) {
        int next_i = (i + 1) % n;
        int last_i = (i - 1 + n) % n;
        Vector v1(another.vertices[last_i].x - another.vertices[i].x,
            another.vertices[last_i].y - another.vertices[i].y, 0);
        Vector v2(another.vertices[next_i].x - another.vertices[i].x,
            another.vertices[next_i].y - another.vertices[i].y, 0);
        angle_another.push_back(std::fabs(v1 % v2 / (v1.len() * v2.len())));
    }
    for (int i = 0; i < n; i++) {
        bool can_find_sim = true;
        for (int j = 0; j < n; j++) {
            if (angle_this[j] != angle_another[(j + i) % n]) {
                can_find_sim = false;
                break;
            }
        }
        if (can_find_sim) {
            for (int j = 0; j < n; j++) {
                int n_j = (j + 1) % n;
                int n_ji = (j + i + 1) % n;
                Vector v1(this->vertices[n_j].x - this->vertices[j].x,
                    this->vertices[n_j].y - this->vertices[j].y, 0);
                Vector v2(another.vertices[n_ji].x - another.vertices[(j + i) % n].x,
                    another.vertices[n_ji].y - another.vertices[(j + i) % n].y,
                    0);
                if (v1.len() != v2.len()) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}
// reflex_point
void Shape::reflex(Point center) {
    for (int i = 0; i < this->vertices.size(); i++) {
        this->vertices[i].x = (center.x + center.x - this->vertices[i].x);
        this->vertices[i].y = (center.y + center.y - this->vertices[i].y);
    }
}
// reflex_line
void Shape::reflex(Line axis) {
    int n = this->vertices.size();
    Vector l(axis.first_point.x - axis.second_point.x,
        axis.first_point.y - axis.second_point.y, 0);
    for (int i = 0; i < n; i++) {
        Vector v(this->vertices[i].x - axis.second_point.x,
            this->vertices[i].y - axis.second_point.y, 0);
        Vector vv = l;
        double scl = ((v % l) / (l % l));
        vv = vv * 2;
        vv = vv * scl;
        vv.x += (axis.second_point.x - v.x);
        vv.y += (axis.second_point.y - v.y);
        this->vertices[i].x = vv.x;
        this->vertices[i].y = vv.y;
    }
    std::reverse(this->vertices.begin(), this->vertices.end());
}
// scale
void Shape::scale(Point center, double coefficient) {
    for (int i = 0; i < this->vertices.size(); i++) {
        this->vertices[i].x =
            center.x + coefficient * (this->vertices[i].x - center.x);
        this->vertices[i].y =
            center.y + coefficient * (this->vertices[i].y - center.y);
    }
}
// rotate
void Shape::rotate(Point center, double angle) {
    angle = (angle * pi) / 180.0;
    int n = this->vertices.size();
    for (int i = 0; i < n; i++) {
        double xx = this->vertices[i].x, yy = this->vertices[i].y, x0 = center.x,
            y0 = center.y;
        double sin_a = sin(angle);
        double cos_a = cos(angle);
        double cos_res = (xx - x0) * cos_a;
        double sin_res = (yy - y0) * sin_a;
        double exp = 1e7;
        this->vertices[i].x = (cos_res - sin_res);
        this->vertices[i].y = y0 + (xx - x0) * sin_a + (yy - y0) * cos_a;
    }
}
