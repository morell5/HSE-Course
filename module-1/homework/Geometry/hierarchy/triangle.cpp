#include "triangle.h"
#include "operations.h"

Triangle::Triangle(const Point& a, const Point& b, const Point& c): Polygon({a, b, c}) {}

Circle Triangle::circumscribedCircle() const {
    Point first_side_center = (vertices_[0] + vertices_[1]) * 0.5;
    Point second_side_center = (vertices_[1] + vertices_[2]) * 05;

    Point first_side_vector = vertices_[0] - vertices_[1];
    Point second_side_vector = vertices_[2] - vertices_[1];

    Point first_side_perpendicular_vector{-first_side_vector.y, first_side_vector.x};
    Point second_side_perpendicular_vector{-second_side_vector.y, second_side_vector.x};

    Line first_side_perpendicular{first_side_perpendicular_vector + first_side_center, first_side_center};
    Line second_side_perpendicular{second_side_perpendicular_vector + second_side_center, second_side_center};

    Point intersection_point = intersectLines(first_side_perpendicular, second_side_perpendicular);
    double radius = PointOperations::hypot(intersection_point, vertices_[0]);
    return {intersection_point, radius};
}


Circle Triangle::inscribedCircle() const {
    Point first_side = vertices_[1] - vertices_[0];
    Point second_side = vertices_[2] - vertices_[0];
    Point third_side = vertices_[2] - vertices_[1];

    double bisector_angle1 = acos(PointOperations::dotProduct(first_side, second_side) /
        PointOperations::hypot(first_side) / PointOperations::hypot(second_side)) / 2;
    Point rotated_first_side_vector{
        first_side.x * cos(bisector_angle1) - first_side.y * sin(bisector_angle1),
        first_side.x * sin(bisector_angle1) + first_side.y * cos(bisector_angle1)
    };
    Line first_bisector_line{vertices_[0], vertices_[0] + rotated_first_side_vector};

    double bisector_angle2 = acos(PointOperations::dotProduct(second_side, third_side) /
        PointOperations::hypot(second_side) / PointOperations::hypot(third_side)) / 2;
    Point rotated_second_side_vector{
        second_side.x * cos(bisector_angle2) - second_side.y * sin(bisector_angle2),
        second_side.x * sin(bisector_angle2) + second_side.y * cos(bisector_angle2)
    };
    Line second_bisector_line{vertices_[2], vertices_[2] + rotated_second_side_vector};
    Point intersection_point = intersectLines(first_bisector_line, second_bisector_line);

    Point intersection_point_vector = intersection_point - vertices_[0];
    double projection_length = PointOperations::dotProduct(first_side, intersection_point_vector) / PointOperations::hypot(first_side);
    double height_length = sqrt(PointOperations::hypot(intersection_point_vector) * PointOperations::hypot(intersection_point_vector) -
        projection_length * projection_length);
    return Circle(intersection_point, height_length);
}


Point Triangle::intersectLines(const Line& first, const Line& second) {
    const auto& first_components = first.getFormulaComponents();
    const auto& second_components = second.getFormulaComponents();

    double x_nominator = -(first_components.c * second_components.y_coef -
        second_components.c * first_components.y_coef);
    double denominator = (first_components.x_coef * second_components.y_coef -
        second_components.x_coef * first_components.y_coef);
    double y_nominator = -(first_components.x_coef * second_components.c -
        second_components.x_coef * first_components.c);

    return {x_nominator / denominator, y_nominator / denominator};
}

