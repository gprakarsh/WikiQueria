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
    bool vertexExists(size_t id);
    bool areAdjacent(Vertex& v1, Vertex& v2);
    void insertEdge(Vertex& v1, Vertex& v2); // Use Disjoint Sets + Path Compression to check for good query
    void removeEdge(Vertex& v1, Vertex& v2);
    std::list<EdgeListIterator>& incidentEdges(Vertex& v);
    void displayGraph();
    const std::unordered_map<size_t, Vertex>& vertexMap();
    const std::list<Edge>& edgeList();
  private:
    //
    std::unordered_map<size_t, Vertex> vertexMap_;
    std::unordered_map<size_t, std::list<EdgeListIterator>> adjList_;
    std::list<Edge> edgeList_;
    size_t edgeNum_;
  };

