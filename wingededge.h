#ifndef DELAUNAYTRIANGULATION_WINGEDEDGE_H
#define DELAUNAYTRIANGULATION_WINGEDEDGE_H

#include <vector>
#include <array>

namespace WED {
    struct Vertex;
    struct Edge;
    struct Face;

    struct Point {
        double x;
        double y;
    };

    struct Vertex {
        Point point;
        Edge* edge;
    };

    struct Edge {
        Vertex* vtxInit;
        Vertex* vtxEnd;
        Face* faceLeft;
        Face* faceRight;
    };

    struct Face {
        Edge* edge0;
        Edge* edge1;
        Edge* edge2;
    };

    enum class Orientation {
        LEFT, RIGHT, COLLINEAR
    };

    static Orientation orientation(Point a, Point b, Point c);

    static bool pointInsideTriangle(Face* face, Point pt);

    static std::array<Vertex*, 3> getFaceVertices(Face* pFace);

    static bool linesCrossing(WED::Point point, WED::Point point1, WED::Point point2, WED::Point point3);

    class WingedEdge {
    private:
        std::vector<Face*> mFaces;
    public:
        WingedEdge(std::array<Point, 3> pts);

        ~WingedEdge();

        bool addTriangles(Point pt);

        Face* faceThatContains(Point pt);
    };
}

#endif //DELAUNAYTRIANGULATION_WINGEDEDGE_H
