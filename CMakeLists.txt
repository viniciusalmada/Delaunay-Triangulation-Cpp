cmake_minimum_required(VERSION 3.17)
project(DelaunayTriangulation)

set(CMAKE_CXX_STANDARD 11)

include_directories("include")

add_executable(DelaunayTriangulation main.cpp halfedge.h halfedge.h topo.h topo.cpp include/compgeom.h compgeom.cpp src/Vertex.cpp include/Vertex.h src/HedEdge.cpp include/HedEdge.h)