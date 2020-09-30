#include "rectangle.h"
#include "operations.h"


Rectangle::Rectangle(const Point& bottom_diag_pt, const Point& top_diag_pt, double factor) {
    double my_factor = 1 / factor;
    double diag_length = PointOperations::hypot(top_diag_pt, bottom_diag_pt);
    double width = diag_length / sqrt(1 + my_factor * my_factor);
    double length = width * my_factor;

    double bottom_diag_side_angle_cos = (length * length + diag_length * diag_length - width * width) / (2 * length * diag_length);
    double bottom_diag_side_angle_sin = sqrt(1 - bottom_diag_side_angle_cos * bottom_diag_side_angle_cos);

    Point diag_direction = PointOperations::norm(top_diag_pt - bottom_diag_pt);
    double rotated_x = diag_direction.x * bottom_diag_side_angle_cos - diag_direction.y * bottom_diag_side_angle_sin;
    double rotated_y = diag_direction.x * bottom_diag_side_angle_sin + diag_direction.y * bottom_diag_side_angle_cos;
    Point rotated_diag_direction{rotated_x, rotated_y};
    Point top_left_point = rotated_diag_direction * length + bottom_diag_pt;

    double top_diag_side_angle_cos = (width * width + diag_length * diag_length - length * length) / (2 * width * diag_length);
    double top_diag_side_angle_sin = sqrt(1 - top_diag_side_angle_cos * top_diag_side_angle_cos);

    rotated_x = diag_direction.x * top_diag_side_angle_cos + diag_direction.y * top_diag_side_angle_sin;
    rotated_y = -diag_direction.x * top_diag_side_angle_sin + diag_direction.y * top_diag_side_angle_cos;
    Point rotated_diag_direction2{rotated_x, rotated_y};
    Point bottom_right_point = rotated_diag_direction2 * width + bottom_diag_pt;

    vertices_ = {top_diag_pt, bottom_right_point, bottom_diag_pt, top_left_point};
}

Point Rectangle::center() const {
    const auto& vertices = getVertices();
    return (vertices[0] + vertices[2]) * 0.5;
}

std::pair<Line, Line> Rectangle::diagonals() const {
    const auto& vertices = getVertices();
    return {{vertices[0], vertices[2]}, {vertices[1], vertices[3]}};
}


