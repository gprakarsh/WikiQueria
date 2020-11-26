#pragma once

// // // Files // // //

#include "Vertex.h"
#include "Edge.h"

// // // Modules // // //
#include <iostream>
#include <unordered_map>
#include <list> 

class Graph{
  public:
    Graph();
    void insertVertex(Vertex& v);
    void removeVertex(Vertex& v);
    bool areAdjacent(Vertex& v1, Vertex& v2);
    void insertEdge(Vertex& v1, Vertex& v2); // Use Disjoint Sets + Path Compression to check for good query
    void removeEdge(Vertex& v1, Vertex& v2);
    std::list<Edge>* incidentEdges(Vertex& v);
    void displayGraph();
  private:
    std::unordered_map<Vertex*, std::list<Edge>*>* AdjList;
    size_t edgeNum;
  };

