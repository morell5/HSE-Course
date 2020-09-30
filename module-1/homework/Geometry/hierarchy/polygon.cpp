
#include "polygon.h"
#include "operations.h"
#include "constants.h"
#include <cmath>
#include <algorithm>

double Polygon::perimeter() const {
    double perimeter = 0;
    int vertices_count = verticesCount();
    for (int i = 0; i < vertices_count; ++i) {
        perimeter += PointOperations::hypot(vertices_[i], vertices_[(i + 1) % vertices_count]);
    }

    return perimeter;
}

double Polygon::area() const {
    Point inside_point = (vertices_[0], vertices_[1]) * 0.5;
    double area_sum = 0;

    int vertices_count = verticesCount();
    for (int i = 0; i < vertices_count; ++i) {
        const Point& curr = vertices_[i];
        const Point& next = vertices_[(i + 1) % vertices_count];

        area_sum += fabs(PointOperations::crossProduct(curr - inside_point, next - inside_point));
    }

    return area_sum / 2;
}

bool Polygon::operator==(const Shape& another) const {
    const auto* another_polygon = dynamic_cast<const Polygon*>(&another);
    if (another_polygon != nullptr) {
        int vertices_count = this->verticesCount();
        if (another_polygon->verticesCount() != vertices_count) {
            return false;
        }
        int vertex_offset = std::find(vertices_.begin(), vertices_.end(), another_polygon->vertices_[0]) - vertices_.begin();
        if (vertex_offset >= vertices_count) {
            return false;
        }

        for (int i = 0; i < vertices_count; ++i) {
            const Point& self_point = vertices_[(i + vertex_offset) % vertices_count];
            if (self_point != another_polygon->vertices_[i]) {
                return false;
            }
        }

        return true;
    }
    return false;
}

bool Polygon::isCongruentTo(const Shape& another) const {
    const auto* another_polygon = dynamic_cast<const Polygon*>(&another);
    if (another_polygon != nullptr) {
        int vertices_count = this->verticesCount();
        if (another_polygon->verticesCount() != vertices_count) {
            return false;
        }

        const auto& self_lengths_and_angles = this->getLengthAndAngles();
        const auto& another_length_and_angles = another_polygon->getLengthAndAngles();

        for (int shift = 0; shift < vertices_count; ++shift) {
            bool are_equal = true;
            for (int i = 0; i < vertices_count; ++i) {
                are_equal &= fabs(self_lengths_and_angles.first[i] - another_length_and_angles.first[i]) < GeometryConstants::EPS;
                are_equal &= fabs(self_lengths_and_angles.second[i] - another_length_and_angles.second[i]) < GeometryConstants::EPS;
            }
            if (are_equal) {
                return true;
            }
        }

        return false;
    }
    return false;
}

bool Polygon::isSimilarTo(const Shape& another) const {
    const auto* another_polygon = dynamic_cast<const Polygon*>(&another);
    if (another_polygon != nullptr) {
        int vertices_count = this->verticesCount();
        if (another_polygon->verticesCount() != vertices_count) {
            return false;
        }

        const auto& self_lengths_and_angles = this->getLengthAndAngles();
        const auto& another_length_and_angles = another_polygon->getLengthAndAngles();
        double factor = another_length_and_angles.first[0] / self_lengths_and_angles.first[0];
        for (int shift = 0; shift < vertices_count; ++shift) {
            bool are_equal = true;
            for (int i = 0; i < vertices_count; ++i) {
                are_equal &= fabs(self_lengths_and_angles.first[i] * factor - another_length_and_angles.first[i]) < GeometryConstants::EPS;
                are_equal &= fabs(self_lengths_and_angles.second[i] - another_length_and_angles.second[i]) < GeometryConstants::EPS;
            }
            if (are_equal) {
                return true;
            }
        }

        return false;
    }
    return false;
}

bool Polygon::containsPoint(const Point& point) const {
    double angle_sum = 0;
    int vertices_count = verticesCount();
    for (int i = 0; i < vertices_count; ++i) {
        int next = (i + 1) % vertices_count;
        Point curr_norm = vertices_[i] - point;
        Point next_norm = vertices_[next] - point;
        double cross_product = PointOperations::crossProduct(curr_norm, next_norm);
        double dot_product = PointOperations::dotProduct(curr_norm, next_norm);
        if (fabs(cross_product) < GeometryConstants::EPS && dot_product <= 0) {
            return true;
        } else {
            angle_sum += atan2(cross_product, dot_product);
        }
    }
    return fabs(angle_sum - 2 * GeometryConstants::PI) < GeometryConstants::EPS;
}

void Polygon::rotate(const Point& center, double angle) {
    double radians_angle = angle / 180 * GeometryConstants::PI;

    int vertices_count = vertices_.size();
    for (int i = 0; i < vertices_count; ++i) {
        Point diff_with_center = vertices_[i] - center;
        Point rotated{
            diff_with_center.x * cos(radians_angle) - diff_with_center.y * sin(radians_angle),
            diff_with_center.x * sin(radians_angle) + diff_with_center.y * cos(radians_angle)
            };
        vertices_[i] = rotated + center;
    }
}

void Polygon::reflex(const Point& center) {
    int vertices_count = vertices_.size();
    for (int i = 0; i < vertices_count; ++i) {
        Point diff_with_center = center - vertices_[i];
        vertices_[i] = vertices_[i] + diff_with_center * 2;
    }
}

void Polygon::reflex(const Line& axis) {
    Point line_vector = axis.getSecondPoint() - axis.getFirstPoint();
    Point normed_line_vector = PointOperations::norm(line_vector);
    int vertices_count = vertices_.size();
    for (int i = 0; i < vertices_count; ++i) {
        Point curr_point_vector = vertices_[i] - axis.getFirstPoint();
        double projection_length = PointOperations::dotProduct(line_vector, curr_point_vector) / PointOperations::hypot(line_vector);

        Point projection = axis.getFirstPoint() + normed_line_vector * projection_length;
        Point diff_with_projection = projection - vertices_[i];
        Point new_point = projection + diff_with_projection;
        vertices_[i] = new_point;
    }
}

void Polygon::scale(const Point& center, double scale) {
    int vertices_count = vertices_.size();

    for (int i = 0; i < vertices_count; ++i) {
        Point curr_diff = vertices_[i] - center;
        Point scaled_diff = curr_diff * scale;
        vertices_[i] = center + scaled_diff;
    }
}

int Polygon::verticesCount() const {
    return vertices_.size();
}

std::vector<Point> Polygon::getVertices() const {
    return vertices_;
}

bool Polygon::isConvex() const {
    double angle_sum = 0;
    int vertices_count = verticesCount();
    int first_product_sign = 0;
    for (size_t i = 0; i < vertices_count; ++i) {
        Point next = vertices_[(i + 1) % vertices_count];
        Point before = vertices_[(i - 1 + vertices_count) % vertices_count];
        Point curr = vertices_[i];

        Point first_vector = curr - before;
        Point second_vector = next - curr;

        double cross_product = PointOperations::crossProduct(first_vector, second_vector);
        if (first_product_sign && first_product_sign * cross_product < 0) {
            return false;
        }
        first_product_sign = cross_product >= 0 ? 1 : 0;

        angle_sum += atan2(cross_product, PointOperations::dotProduct(first_vector, second_vector));
    }

    return fabs(fabs(angle_sum) - 2 * GeometryConstants::PI) < GeometryConstants::EPS;
}

std::pair<std::vector<double>, std::vector<double>> Polygon::getLengthAndAngles() const {
    int vertices_count = verticesCount();
    std::vector<double> self_lengths(vertices_count);
    std::vector<double> self_angles(vertices_count);

    for (int i = 0; i < vertices_count; ++i) {
        Point next = vertices_[(i + 1) % vertices_count];
        Point before = vertices_[(i - 1 + vertices_count) % vertices_count];
        Point curr = vertices_[i];

        Point first_vector = curr - before;
        Point second_vector = next - curr;
        self_angles[i] =
            atan2(PointOperations::crossProduct(first_vector, second_vector),
                  PointOperations::dotProduct(first_vector, second_vector));
        self_lengths[i] = PointOperations::hypot(second_vector);
    }

    return {self_lengths, self_angles};
}
