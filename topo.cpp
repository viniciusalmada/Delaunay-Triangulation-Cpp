#include "topo.h"
#include <cfloat>

Topo::Model::Model(Topo::Point p0, Topo::Point p1, Topo::Point p2) {
    Vertex* v0 = new Vertex;
    Vertex* v1 = new Vertex;
    Vertex* v2 = new Vertex;

    v0->pt = p0;
    v1->pt = p1;
    v2->pt = p2;

    // Edge 0 = v0 .. v1
    // Edge 1 = v1 .. v2
    // Edge 2 = v2 .. v0
    HalfEdge* hed1edge0 = new HalfEdge;
    HalfEdge* hed2edge0 = new HalfEdge;
    HalfEdge* hed1edge1 = new HalfEdge;
    HalfEdge* hed2edge1 = new HalfEdge;
    HalfEdge* hed1edge2 = new HalfEdge;
    HalfEdge* hed2edge2 = new HalfEdge;

    hed1edge0->vtx = v0;
    hed2edge0->vtx = v1;
    hed1edge1->vtx = v1;
    hed2edge1->vtx = v2;
    hed1edge2->vtx = v2;
    hed2edge2->vtx = v0;

    Edge* ed0 = new Edge;
    Edge* ed1 = new Edge;
    Edge* ed2 = new Edge;

    ed0->hed1 = hed1edge0;
    ed0->hed2 = hed2edge0;
    ed1->hed1 = hed1edge1;
    ed1->hed2 = hed2edge1;
    ed2->hed1 = hed1edge2;
    ed2->hed2 = hed2edge2;

    v0->hed = hed1edge0;
    v1->hed = hed1edge1;
    v2->hed = hed1edge2;

    hed1edge0->edge = ed0;
    hed2edge0->edge = ed0;
    hed1edge1->edge = ed1;
    hed2edge1->edge = ed1;
    hed1edge2->edge = ed2;
    hed2edge2->edge = ed2;

    Triangle* tri = new Triangle;

    hed1edge0->tri = tri;
    hed1edge1->tri = tri;
    hed1edge2->tri = tri;

    tri->v0 = v0;
    tri->v1 = v1;
    tri->v2 = v2;

    mFirstTri = tri;
}

Topo::Model::~Model() {
    Triangle* tri = mFirstTri;
    do {
        delete tri->v0->hed->edge;
        delete tri->v1->hed->edge;
        delete tri->v2->hed->edge;

        delete tri->v0->hed;
        delete tri->v1->hed;
        delete tri->v2->hed;

        delete tri->v0;
        delete tri->v1;
        delete tri->v2;

        Triangle* current = tri;

        tri = tri->next;

        delete current;
    } while (tri != nullptr);
}

bool Topo::Model::addTriangles(Topo::Point pt) {
    Triangle* tempTri = Topo::Model::whichTriangleContainsPt(pt);

    if (tempTri == nullptr) return false;

    Vertex* tempTriV0 = new Vertex(*tempTri->v0);
    Vertex* tempTriV1 = new Vertex(*tempTri->v1);
    Vertex* tempTriV2 = new Vertex(*tempTri->v2);
    Triangle* tempTriNext = nullptr;
    if (tempTri->next != nullptr)
        tempTriNext = new Triangle(*tempTri->next);


    Vertex* newV = new Vertex;
    newV->pt = pt;

    HalfEdge* hed1edge0 = new HalfEdge;
    HalfEdge* hed2edge0 = new HalfEdge;
    HalfEdge* hed1edge1 = new HalfEdge;
    HalfEdge* hed2edge1 = new HalfEdge;
    HalfEdge* hed1edge2 = new HalfEdge;
    HalfEdge* hed2edge2 = new HalfEdge;

    hed1edge0->vtx = newV;
    hed1edge1->vtx = newV;
    hed1edge2->vtx = newV;

    hed2edge0->vtx = tempTriV0;
    hed2edge1->vtx = tempTriV1;
    hed2edge2->vtx = tempTriV2;

    newV->hed = hed1edge0;

    Edge* edge0 = new Edge;
    Edge* edge1 = new Edge;
    Edge* edge2 = new Edge;

    edge0->hed1 = hed1edge0;
    edge0->hed2 = hed2edge0;
    edge1->hed1 = hed1edge1;
    edge1->hed2 = hed2edge1;
    edge2->hed1 = hed1edge2;
    edge2->hed2 = hed2edge2;

    hed1edge0->edge = edge0;
    hed2edge0->edge = edge0;
    hed1edge1->edge = edge1;
    hed2edge1->edge = edge1;
    hed1edge2->edge = edge2;
    hed2edge2->edge = edge2;

    Triangle* newTri0 = new Triangle;
    Triangle* newTri1 = new Triangle;
    Triangle* newTri2 = new Triangle;

    newTri0->v0 = newV;
    newTri0->v1 = tempTriV0;
    newTri0->v2 = tempTriV1;

    newTri1->v0 = newV;
    newTri1->v1 = tempTriV1;
    newTri1->v2 = tempTriV2;

    newTri2->v0 = newV;
    newTri2->v1 = tempTriV2;
    newTri2->v2 = tempTriV0;

    if (tempTri == mFirstTri) {
        mFirstTri = newTri0;
        newTri0->next = newTri1;
        newTri1->next = newTri2;
        newTri2->next = nullptr;
    } else {
        Triangle* next = tempTriNext;
        newTri0->next = newTri1;
        newTri1->next = newTri2;
        newTri2->next = next;
    }

    hed1edge0->tri = newTri2;
    hed2edge0->tri = newTri0;
    hed1edge1->tri = newTri0;
    hed2edge1->tri = newTri1;
    hed1edge2->tri = newTri1;
    hed2edge2->tri = newTri2;

    delete tempTri;

    return true;
}

Topo::Triangle* Topo::Model::whichTriangleContainsPt(Topo::Point point) {
    Triangle* tri = mFirstTri;
    while (tri != nullptr) {
        if (containsPt(tri, point))
            return tri;

        tri = tri->next;
    }
    return nullptr;
}

bool Topo::Model::containsPt(Topo::Triangle* tri, Topo::Point pt) {

    Topo::Point ptInf = Topo::Point{pt.x, DBL_MAX};

    bool ab = linesIntersection(tri->v0->pt, tri->v1->pt, pt, ptInf);
    bool bc = linesIntersection(tri->v1->pt, tri->v2->pt, pt, ptInf);
    bool ca = linesIntersection(tri->v2->pt, tri->v0->pt, pt, ptInf);

    int count = 0;
    if (ab) count++;
    if (bc) count++;
    if (ca) count++;

    return count % 2 != 0;
}

Topo::HalfEdge::HalfEdge(Topo::Vertex v, Topo::Edge e, Topo::Triangle t) : vtx(v), edge(e), tri(t) {}
