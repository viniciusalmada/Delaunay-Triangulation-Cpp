#ifndef DELAUNAY_TRIANGULATION_COMPGEOM_H
#define DELAUNAY_TRIANGULATION_COMPGEOM_H

namespace CG {
    enum class Orientation {
        LEFT, RIGHT, COLLINEAR
    };

    struct Point {
        double x;
        double y;

        Point operator+(const Point& a) const {
            return Point{x + a.x, y + a.y};
        }
    };

    bool linesIntersection(Point a, Point b, Point c, Point d);

    Orientation orientation(Point a, Point b, Point c);
}

#endif //DELAUNAY_TRIANGULATION_COMPGEOM_H
