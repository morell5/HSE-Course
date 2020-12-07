<<<<<<< HEAD

=======
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
#include "polygon.h"
#include <algorithm>

Polygon::Polygon(const std::vector<Point>& a) {
    for (int i = 0; i < a.size(); i++) {
        this->vertices.push_back(a[i]);
    }
}

Polygon::Polygon() {}

<<<<<<< HEAD
std::vector<Point> Polygon::getVertices() {
    std::vector<Point> result;
    for (int i = 0; i < this->vertices.size(); i++) {
=======
std::vector<Point> Polygon::getVertices()
{
    std::vector<Point> result;
    for (int i = 0; i < this->vertices.size(); i++)
    {
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
        result.push_back(Point(this->vertices[i].x, this->vertices[i].y));
    }
    return result;
}

<<<<<<< HEAD
int Polygon::verticesCount() { return this->vertices.size(); }

// выпуклая оболочка
const bool operator<(const Point& first, const Point& second) {
    return first.x < second.x || first.x == second.x && first.y < second.y;
}

double len(Point p) { return p.x * p.x + p.y * p.y; }

const Point operator-(Point& first, Point& second) {
=======
int Polygon::verticesCount()
{
    return this->vertices.size();
}

// выпуклая оболочка
const bool operator < (const Point& first, const Point& second)
{
    return first.x < second.x || first.x == second.x && first.y < second.y;
}

double len(Point p) {
    return p.x * p.x + p.y * p.y;
}

const Point operator - (Point& first, Point& second) {
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
    Point v;
    v.x = first.x - second.x;
    v.y = first.y - second.y;
    return v;
}

<<<<<<< HEAD
const Point operator+(Point& first, Point& second) {
=======
const Point operator + (Point& first, Point& second) {
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
    Point v;
    v.x = first.x + second.x;
    v.y = first.y + second.y;
    return v;
}

<<<<<<< HEAD
const double operator*(Point& first, Point& second) {
=======
const double operator * (Point& first, Point& second) {
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
    return first.x * second.y - first.y * second.x;
}

bool Polygon::isConvex() {
    Point mp;
    std::vector<Point> all_vert = this->getVertices();
    std::vector<Point> shell_vert;
    int n = this->verticesCount();
    mp = all_vert[1];
<<<<<<< HEAD
    for (int i = 1; i <= n; i++) {
        if (all_vert[i].y < mp.y || all_vert[i].y == mp.y && all_vert[i].x < mp.x) {
            mp = all_vert[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        all_vert[i] = all_vert[i] - mp;
    }
    std::sort(all_vert.begin(), all_vert.end());
    for (int i = 1; i <= n; i++) {
        while (shell_vert.size() > 1) {
            int s = shell_vert.size() - 1;
            Point v1 = shell_vert[s] - shell_vert[s - 1];
            Point v2 = all_vert[i] - shell_vert[s];
            if (v1 * v2 > 0) {
                break;
            }
            else {
=======
    for (int i = 1; i <= n; i++)
    {
        if (all_vert[i].y < mp.y || all_vert[i].y == mp.y && all_vert[i].x < mp.x)
        {
            mp = all_vert[i];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        all_vert[i] = all_vert[i] - mp;
    }
    std::sort(all_vert.begin(), all_vert.end());
    for (int i = 1; i <= n; i++)
    {
        while (shell_vert.size() > 1)
        {
            int s = shell_vert.size() - 1;
            Point v1 = shell_vert[s] - shell_vert[s - 1];
            Point v2 = all_vert[i] - shell_vert[s];
            if (v1 * v2 > 0)
            {
                break;
            }
            else
            {
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
                shell_vert.pop_back();
            }
        }
        shell_vert.push_back(all_vert[i]);
    }
    shell_vert.push_back(shell_vert[0]);
<<<<<<< HEAD
    if (shell_vert.size() != all_vert.size()) {
=======
    if (shell_vert.size() != all_vert.size())
    {
>>>>>>> c02a9c51073af2aeb3ecac63b686daabced17a76
        return false;
    }
    return true;
}

