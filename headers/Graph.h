#pragma once

// // // Files // // //

#include "Vertex.h"
#include "Edge.h"

// // // Modules // // //
#include <unordered_map>
#include <list>
#include <vector> 

using std::unordered_map;
using std::list;
using std::vector;

class Graph{
  public:
    Graph();
    void insertVertex(const Vertex& v);
    void removeVertex(const Vertex& v);
    bool edgeExists(const Vertex& source,const Vertex& destination);
    bool vertexExists(const Vertex& v);
    void insertEdge(Vertex& source,Vertex& destination); // Use Disjoint Sets + Path Compression to check for good query
    void removeEdge(const Vertex& source,const Vertex& destination);
    vector<Vertex> incidentVertices(const Vertex& v);
    vector<Edge> incidentEdges(const Vertex& v);
    void displayGraph();
  private:
    unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> adjacency_list;
};


/*
  A=>B=>A-B  
     C=>A-C
     D=>D-A // store vertices which have dest to A in a vector
  B => 
  C =>
  D => A => D-A
vec[i][A]
*/

