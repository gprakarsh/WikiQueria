#pragma once

#include <iostream>
#include "../Vertex.h"

class Graph{
  public:
    void insertVertex(Vertex key);
    void removeVertex(Vertex v);
    bool areAdjacent(Vertex v1, Vertex v2);
    void insertEdge(Vertex v1, Vertex v2, int weight);
    // Use Disjoint Sets + Path Compression to check for good query
    void removeEdge(Vertex v1, Vertex v2);
  private:
    
};