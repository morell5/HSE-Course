#include <vector>
#include "ellipse.h"
#include "constants.h"
#include "operations.h"

Ellipse::Ellipse(const Point& a, const Point& b, double dist_sum): foci_a_(a), foci_b_(b) {
    a_ = dist_sum / 2;
}

double Ellipse::getC() const {
    return PointOperations::hypot(foci_a_, foci_b_) / 2;
}

double Ellipse::perimeter() const {
    double c = getC();
    double b = sqrt(a_ * a_ - c * c);
    return 4 * (GeometryConstants::PI * a_ * b + (a_ - b)) / (a_ + b);
}

std::pair<Point, Point> Ellipse::focuses() const {
    return {foci_a_, foci_b_};
}

double Ellipse::eccentricity() const {
    return getC() / a_;
}

Point Ellipse::center() const {
    return (foci_a_ + foci_b_) * 0.5;
}

double Ellipse::area() const {
    double c = getC();
    double b = sqrt(a_ * a_ - c * c);

    return GeometryConstants::PI * a_ * b;
}

bool Ellipse::operator==(const Shape& another) const {
    const auto* another_ellipse = dynamic_cast<const Ellipse*>(&another);
    if (another_ellipse != nullptr) {
        return ((foci_a_ == another_ellipse->foci_a_ && foci_b_ == another_ellipse->foci_b_) ||
        (foci_a_ == another_ellipse->foci_b_ && foci_b_ == another_ellipse->foci_a_)) &&
        fabs(a_ - another_ellipse->a_) < GeometryConstants::EPS;
    }
    return false;
}

bool Ellipse::isCongruentTo(const Shape& another) const {
    const auto* another_ellipse = dynamic_cast<const Ellipse*>(&another);
    if (another_ellipse != nullptr) {
        return (
            (fabs(PointOperations::hypot(foci_a_, foci_b_) -
            PointOperations::hypot(another_ellipse->foci_a_, another_ellipse->foci_b_)) < GeometryConstants::EPS) &&
            (fabs(a_ - another_ellipse->a_) < GeometryConstants::EPS)
        );
    }
    return false;
}

bool Ellipse::isSimilarTo(const Shape& another) const {
    const auto* another_ellipse = dynamic_cast<const Ellipse*>(&another);
    if (another_ellipse != nullptr) {
        double factor = PointOperations::hypot(foci_a_, foci_b_) / PointOperations::hypot(another_ellipse->foci_a_, another_ellipse->foci_b_);
        return fabs(a_ - another_ellipse->a_ * factor) < GeometryConstants::EPS;
    }
    return false;
}

bool Ellipse::containsPoint(const Point& point) const {
    return PointOperations::hypot(foci_a_, point) + PointOperations::hypot(foci_b_, point) <= 2 * a_;
}

void Ellipse::rotate(const Point& center, double angle) {
    std::vector<Point> focis{foci_a_, foci_b_};
    double radians_angle = angle / 180 * GeometryConstants::PI;
    for (int i = 0; i < 2; ++i) {
        Point diff_with_center = focis[i] - center;
        Point rotated{
            diff_with_center.x * cos(radians_angle) - diff_with_center.y * sin(radians_angle),
            diff_with_center.x * sin(radians_angle) + diff_with_center.y * cos(radians_angle)
        };
        focis[i] = rotated + center;
    }
    foci_a_ = focis[0];
    foci_b_ = focis[1];
}

void Ellipse::reflex(const Point& center) {
    std::vector<Point> focis{foci_a_, foci_b_};
    for (int i = 0; i < 2; ++i) {
        Point diff_with_center = center - focis[i];
        focis[i] = focis[i] + diff_with_center * 2;
    }
    foci_a_ = focis[0];
    foci_b_ = focis[1];
}

void Ellipse::reflex(const Line& axis) {
    Point line_vector = axis.getSecondPoint() - axis.getFirstPoint();
    Point normed_line_vector = PointOperations::norm(line_vector);
    std::vector<Point> focis{foci_a_, foci_b_};
    for (int i = 0; i < 3; ++i) {
        Point curr_point_vector = focis[i] - axis.getFirstPoint();
        double projection_length = PointOperations::dotProduct(line_vector, curr_point_vector) / PointOperations::hypot(line_vector);

        Point projection = axis.getFirstPoint() + normed_line_vector * projection_length;
        Point diff_with_projection = projection - focis[i];
        Point new_point = projection + diff_with_projection;
        focis[i] = new_point;
    }
    foci_a_ = focis[0];
    foci_b_ = focis[1];
}

void Ellipse::scale(const Point& center, double scale) {
    std::vector<Point> focis{foci_a_, foci_b_};
    for (int i = 0; i < 2; ++i) {
        Point curr_diff = focis[i] - center;
        Point scaled_diff = curr_diff * scale;
        focis[i] = center + scaled_diff;
    }
    foci_a_ = focis[0];
    foci_b_ = focis[1];
    a_ *= scale;
}

