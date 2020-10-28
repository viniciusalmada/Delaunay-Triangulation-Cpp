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
//        Face* faceLeft;
//        Face* faceRight;
    };

    struct Face {
        Edge* edge0;
        Edge* edge1;
        Edge* edge2;
    };

    enum class Orientation {
        LEFT, RIGHT, COLLINEAR
    };

    class WingedEdge {
    private:
        std::vector<Face*> mFaces;
    public:
        WingedEdge(std::array<Point, 3> pts);

        ~WingedEdge();

        bool addTriangles(Point pt);

        Face* faceThatContains(Point pt);

        static Orientation orientationPointToEdge(Edge* edge, Point pt);

        static bool pointInsideTriangle(Face* face, Point pt);

        static std::array<Vertex*, 3> getFaceVertices(Face* pFace);
    };
}

#endif //DELAUNAYTRIANGULATION_WINGEDEDGE_H
