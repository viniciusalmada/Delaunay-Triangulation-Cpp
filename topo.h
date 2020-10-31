/*
#ifndef DELAUNAY_TRIANGULATION_TOPO_H
#define DELAUNAY_TRIANGULATION_TOPO_H

#include <vector>
#include "include/compgeom.h"

namespace Topo {
    using CG::Point;

    struct Edge;

    struct HalfEdge;

    struct Triangle;

    struct Vertex {
    public:
        Point pt{};
        HalfEdge hed;
    };

    struct HalfEdge {
    public:
        Vertex vtx;
        Edge edge;
        Triangle tri;
        HalfEdge(Vertex v, Edge e, Triangle t);
    };

    struct Edge {
    public:
        HalfEdge hed1;
        HalfEdge hed2;
    };

    struct Triangle {
    public:
        Vertex v0;
        Vertex v1;
        Vertex v2;
        Triangle next;
    };

    struct Model {
    private:
        Triangle mFirstTri;
    public:
        Model(Point p0, Point p1, Point p2);

        ~Model();

        bool addTriangles(Point pt);

        Triangle whichTriangleContainsPt(Point point);

        static bool containsPt(Triangle tri, Point pt);

    };
}

#endif //DELAUNAY_TRIANGULATION_TOPO_H
*/
