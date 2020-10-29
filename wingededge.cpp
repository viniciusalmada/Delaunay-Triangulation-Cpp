#include "wingededge.h"
#include "cfloat"

WED::Orientation WED::orientation(WED::Point a, WED::Point b, WED::Point c) {
    double det = (a.x * b.y + b.x * c.y + c.x * a.y) - (a.x * c.y + b.x * a.y + c.x * b.y);

    if (det > 0.0)
        return WED::Orientation::LEFT;
    else if (det < 0.0)
        return WED::Orientation::RIGHT;
    else
        return WED::Orientation::COLLINEAR;
}

std::array<WED::Vertex*, 3> WED::getFaceVertices(WED::Face* face) {
    Vertex* v0 = face->edge0->vtxInit;
    Vertex* v1 = face->edge0->vtxEnd;
    Vertex* v2;
    if (face->edge1->vtxInit == v0)
        v2 = face->edge1->vtxEnd;
    else
        v2 = face->edge1->vtxInit;

    return std::array<WED::Vertex*, 3>{v0, v1, v2};
}

bool WED::pointInsideTriangle(WED::Face* face, WED::Point pt) {

    WED::Point ptInf = WED::Point{pt.x, DBL_MAX};
    std::array<WED::Vertex*, 3> vtxPoints = WED::getFaceVertices(face);

    bool ab = linesCrossing(vtxPoints[0]->point, vtxPoints[1]->point, pt, ptInf);
    bool bc = linesCrossing(vtxPoints[1]->point, vtxPoints[2]->point, pt, ptInf);
    bool ca = linesCrossing(vtxPoints[2]->point, vtxPoints[0]->point, pt, ptInf);

    int count = 0;
    if (ab) count++;
    if (bc) count++;
    if (ca) count++;

    return count % 2 != 0;
}

bool WED::linesCrossing(WED::Point a, WED::Point b, WED::Point c, WED::Point d) {
    return WED::orientation(a, b, c) != WED::orientation(a, b, d) &&
           WED::orientation(c, d, a) != WED::orientation(c, d, b);
}

WED::WingedEdge::WingedEdge(std::array<Point, 3> pts) {
    Vertex* v0 = new Vertex{};
    Vertex* v1 = new Vertex{};
    Vertex* v2 = new Vertex{};

    v0->point = pts[0];
    v1->point = pts[1];
    v2->point = pts[2];

    Edge* edge0 = new Edge{};
    Edge* edge1 = new Edge{};
    Edge* edge2 = new Edge{};

    v0->edge = edge0;
    v1->edge = edge1;
    v2->edge = edge2;

    edge0->vtxInit = v0;
    edge0->vtxEnd = v1;
    edge1->vtxInit = v1;
    edge1->vtxEnd = v2;
    edge2->vtxInit = v2;
    edge2->vtxEnd = v0;

    Face* face = new Face{};
    face->edge0 = edge0;
    face->edge1 = edge1;
    face->edge2 = edge2;

    edge0->faceLeft = face;
    edge1->faceLeft = face;
    edge2->faceLeft = face;

    edge0->faceRight = nullptr;
    edge1->faceRight = nullptr;
    edge2->faceRight = nullptr;

    this->mFaces.push_back(face);
}

WED::WingedEdge::~WingedEdge() {
    for (Face* f : mFaces) {
        delete f->edge0->vtxInit;
        delete f->edge0->vtxEnd;

        delete f->edge1->vtxInit;
        delete f->edge1->vtxEnd;

        delete f->edge2->vtxInit;
        delete f->edge2->vtxEnd;

        delete f->edge0;
        delete f->edge1;
        delete f->edge2;

        delete f;
    }
}

bool WED::WingedEdge::addTriangles(Point pt) {
    Vertex* newVtx = new Vertex{};
    newVtx->point = pt;

    Face* faceToRemove = faceThatContains(pt);
    if (faceToRemove == nullptr) return false;

    Edge* newEdge0 = new Edge{};
    Edge* newEdge1 = new Edge{};
    Edge* newEdge2 = new Edge{};

    newEdge0->vtxInit = newVtx;
    newEdge1->vtxInit = newVtx;
    newEdge2->vtxInit = newVtx;

    Edge* edge0 = faceToRemove->edge0;
    Edge* edge1 = faceToRemove->edge1;
    Edge* edge2 = faceToRemove->edge2;

    newEdge0->vtxEnd = edge0->vtxInit;
    newEdge1->vtxEnd = edge0->vtxEnd;

    if (edge1->vtxInit == edge0->vtxInit)
        newEdge2->vtxEnd = edge1->vtxEnd;
    else if (edge1->vtxInit == edge0->vtxEnd)
        newEdge2->vtxEnd = edge1->vtxInit;
    else
        newEdge2->vtxEnd = edge1->vtxInit;

    Face* newFace0 = new Face{};
    newFace0->edge0 = edge0;
    newFace0->edge1 = newEdge0;
    newFace0->edge2 = newEdge1;

    Face* newFace1 = new Face{};
    newFace1->edge0 = edge1;
    newFace1->edge1 = newEdge1;
    newFace1->edge2 = newEdge2;

    Face* newFace2 = new Face{};
    newFace2->edge0 = edge2;
    newFace2->edge1 = newEdge2;
    newFace2->edge2 = newEdge0;

    newEdge0->faceRight = newFace1;
    newEdge0->faceLeft = newFace0;

    newEdge1->faceRight = newFace2;
    newEdge1->faceLeft = newFace0;
    return false;
}

WED::Face* WED::WingedEdge::faceThatContains(Point pt) {
    for (Face* f : mFaces) {
        if (WED::pointInsideTriangle(f, pt))
            return f;
    }
    return nullptr;
}

