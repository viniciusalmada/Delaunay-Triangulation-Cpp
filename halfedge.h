#ifndef DELAUNAYTRIANGULATION_HALFEDGE_H
#define DELAUNAYTRIANGULATION_HALFEDGE_H

#include <vector>
#include <array>

namespace HED {
    struct Vertex;
    struct Edge;
    struct HalfEdge;
    struct Face;
    struct Loop;

    struct Point {
        double x;
        double y;
    };

    struct Vertex {
        Point point;
        HalfEdge* hed;
    };

    struct Edge {
        HalfEdge* hed1;
        HalfEdge* hed2;
    };

    struct Face {
        Loop* out;
        Loop* in;
    };

    struct Loop {
        HalfEdge* hed;
        Face* face;
        Loop* next;
    };

    enum class Orientation {
        LEFT, RIGHT, COLLINEAR
    };

    class HED {
    private:
        std::vector<Face*> mFaces;
    public:
        HED(std::array<Point, 3> pts);

        ~HED();

        bool addTriangles(Point pt);

        Face* faceThatContains(Point pt);

        static Orientation orientationPointToEdge(Edge* edge, Point pt);

        static std::array<Vertex*, 3> getFaceVertices(Face* pFace);
    };
}

#endif //DELAUNAYTRIANGULATION_WINGEDEDGE_H
