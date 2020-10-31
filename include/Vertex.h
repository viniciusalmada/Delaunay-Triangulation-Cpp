#ifndef DELAUNAY_TRIANGULATION_VERTEX_H
#define DELAUNAY_TRIANGULATION_VERTEX_H

#include "compgeom.h"

namespace Topo {
    class Vertex {
    private:
        CG::Point pt;
        HedEdge hed;
    };
}

#endif //DELAUNAYTRIANGULATION_VERTEX_H
