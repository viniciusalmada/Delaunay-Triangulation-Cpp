# cmake_minimum_required(VERSION <specify CMake version here>)
project(DelaunayTriangulation)

set(CMAKE_CXX_STANDARD 11)

add_executable(DelaunayTriangulation main.cpp wingededge.h wingededge.cpp halfedge.h halfedge.h)