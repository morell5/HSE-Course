#include "line.h"
#include "constants.h"
#include <cmath>


Point Line::getFirstPoint() const {
    return a_;
}

Point Line::getSecondPoint() const {
    return b_;
}

bool operator==(const Line& lhs, const Line& rhs) {
    const Line::LineFormulaComponents& lhs_components = lhs.getFormulaComponents();
    const Line::LineFormulaComponents& rhs_components = rhs.getFormulaComponents();
    double factor = 0;
    if (fabs(lhs_components.x_coef) < GeometryConstants::EPS) {
        if (fabs(rhs_components.y_coef) < GeometryConstants::EPS) {
            return false;
        }
        factor = lhs_components.y_coef / rhs_components.y_coef;
    }

    if (fabs(lhs_components.y_coef) < GeometryConstants::EPS) {
        if (fabs(rhs_components.x_coef) < GeometryConstants::EPS) {
            return false;
        }
        factor = lhs_components.x_coef / rhs_components.x_coef;
    }

    return fabs(lhs_components.x_coef - rhs_components.x_coef * factor) < GeometryConstants::EPS &&
           fabs(lhs_components.y_coef - rhs_components.y_coef * factor) < GeometryConstants::EPS &&
           fabs(lhs_components.c - rhs_components.c * factor) < GeometryConstants::EPS;
}

bool operator!=(const Line& lhs, const Line& rhs) {
    return !(lhs == rhs);
}

Line::LineFormulaComponents Line::getFormulaComponents() const {
    double x_coef = b_.y - a_.y;
    double y_coef = -(b_.x - a_.x);
    double c = -x_coef * a_.x - y_coef * a_.y;

    return LineFormulaComponents{x_coef, y_coef, c};
}


