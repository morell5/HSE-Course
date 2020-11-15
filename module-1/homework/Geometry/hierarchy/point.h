#ifndef TGEO_POINT_H
#define TGEO_POINT_H

struct Point {
  double x{0.0};
  double y{0.0};

  Point() = default;

  Point(double x, double y);

  bool operator==(const Point& o) const;

  bool operator!=(const Point& o) const;

  // Scale point, just multiply it's coordinates
  Point operator*(double value) const;

  Point operator+(const Point& o) const;

  Point& operator+=(const Point& o);

  Point operator-(const Point& o) const;

  Point& operator-=(const Point& o);

  bool operator<(const Point& rhs) const;

  static double distanceBetween(Point a, Point b);

  static void scale(Point& point, Point center, double coefficient);

  static void rotate(Point& point, Point center, double angle);
};

#endif