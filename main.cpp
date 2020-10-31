#include <iostream>
#include <array>
#include "include/compgeom.h"
#include "topo.h"

std::array<CG::Point, 3> genTriangleBox(std::vector<CG::Point>& pts);

int main() {

    std::vector<CG::Point> pts{};

    pts.emplace_back(CG::Point{10.0, 20.0});
    pts.emplace_back(CG::Point{5.0, 25.0});
    pts.emplace_back(CG::Point{-5.0, 10.0});
    pts.emplace_back(CG::Point{4.5, 13.5});

    std::array<CG::Point, 3> triangleBox = genTriangleBox(pts);

    Topo::Model model{triangleBox[0], triangleBox[1], triangleBox[2]};

    model.addTriangles(pts[0]);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

std::array<CG::Point, 3> genTriangleBox(std::vector<CG::Point>& pts) {
    double maxX = pts[0].x;
    double minX = pts[0].x;
    double maxY = pts[0].y;
    double minY = pts[0].y;

    for (CG::Point& pt : pts) {
        maxX = pt.x > maxX ? pt.x : maxX;
        minX = pt.x < minX ? pt.x : minX;
        maxY = pt.x > maxY ? pt.y : maxY;
        minY = pt.x < minY ? pt.y : minY;
    }

    double m;
    if (maxX - minX > maxY - minY)
        m = (maxY - minX) / 2.0;
    else
        m = (maxY - minY) / 2.0;

    double centerX = minX + m;
    double centerY = minY + m;

    CG::Point center{centerX, centerY};

    CG::Point p0 = CG::Point{-3.0 * m, -3.0 * m} + center;
    CG::Point p1 = CG::Point{3.0 * m, 0.0} + center;
    CG::Point p2 = CG::Point{0.0, 3.0 * m} + center;

    return std::array<CG::Point, 3>{p0, p1, p2};
}
