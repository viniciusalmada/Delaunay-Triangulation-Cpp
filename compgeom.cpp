#include "include/compgeom.h"

CG::Orientation CG::orientation(CG::Point a, CG::Point b, CG::Point c) {
    double det = (a.x * b.y + b.x * c.y + c.x * a.y) - (a.x * c.y + b.x * a.y + c.x * b.y);

    if (det > 0.0)
        return CG::Orientation::LEFT;
    else if (det < 0.0)
        return CG::Orientation::RIGHT;
    else
        return CG::Orientation::COLLINEAR;
}

bool CG::linesIntersection(CG::Point a, CG::Point b, CG::Point c, CG::Point d) {
    return CG::orientation(a, b, c) != CG::orientation(a, b, d) &&
           CG::orientation(c, d, a) != CG::orientation(c, d, b);
}