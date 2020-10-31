#ifndef DELAUNAY_TRIANGULATION_HEDEDGE_H
#define DELAUNAY_TRIANGULATION_HEDEDGE_H

#include "Vertex.h"

namespace Topo {
    class HedEdge {
        Vertex vtx;
        Edge edge;
        Triangle tri;
    };
}

#endif //DELAUNAYTRIANGULATION_HEDEDGE_H
