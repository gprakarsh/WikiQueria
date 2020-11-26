#pragma once

// // // Files // // //

#include "Vertex.h"
#include "Edge.h"

// // // Modules // // //
#include <iostream>
#include <unordered_map>
#include <list> 

using EdgeListIterator = std::list<Edge>::iterator;

class Graph{
  public:
    Graph();
    void insertVertex(Vertex& v);
    void removeVertex(Vertex& v);
    bool areAdjacent(Vertex& v1, Vertex& v2);
    void insertEdge(Vertex& v1, Vertex& v2); // Use Disjoint Sets + Path Compression to check for good query
    void removeEdge(Vertex& v1, Vertex& v2);
    std::list<EdgeListIterator>& incidentEdges(Vertex& v);
    void displayGraph();
  private:
    //
    std::unordered_map<size_t, Vertex> vertexMap;
    std::unordered_map<size_t, std::list<EdgeListIterator>> AdjList;
    std::list<Edge> EdgeList;
    size_t edgeNum;
  };

