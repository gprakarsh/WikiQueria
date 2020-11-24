#pragma once

// // // Files // // //
#include "Vertex.h"
#include "Edge.h"

// // // Modules // // //
#include <iostream>
#include <unordered_map>
#include <list> 


// // // Graph ADT // // //
class Graph{
  public:
    void insertVertex(Vertex key);
    void removeVertex(Vertex v);
    bool areAdjacent(Vertex v1, Vertex v2);
    void insertEdge(Vertex v1, Vertex v2, int weight);
    void removeEdge(Vertex v1, Vertex v2);
  private:
    // std::unordered_map<Vertex, std::list<Edge*>> adj_list;
};