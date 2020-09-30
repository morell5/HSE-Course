#include <square.h>
#include "operations.h"

Square::Square(const Point& diag_bot, const Point& diag_top): Rectangle(diag_bot, diag_top, 1) {}


Circle Square::circumscribedCircle() const {
    return Circle((vertices_[0] + vertices_[2]) * 0.5,
                  PointOperations::hypot(vertices_[0], vertices_[2]) / 2);
}

Circle Square::inscribedCircle() const {
    return Circle((vertices_[0] + vertices_[2]) * 0.5,
                  PointOperations::hypot(vertices_[0], vertices_[1]) / 2);
}
