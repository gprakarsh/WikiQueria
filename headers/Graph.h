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

class BFSTraversal;

class Graph{
  public:
    Graph();
    void insertVertex(const Vertex& v);
    void removeVertex(const Vertex& v);
    bool edgeExists(const Vertex& source,const Vertex& destination);
    bool vertexExists(const Vertex& v);
    void insertEdge(Vertex& source,Vertex& destination); // Use Disjoint Sets + Path Compression to check for good query
    void removeEdge(const Vertex& source,const Vertex& destination);
    vector<Vertex> incidentVertices(const Vertex& v) const;
    vector<Edge> incidentEdges(const Vertex& v) const;
    BFSTraversal getBFS(const Vertex& v);
    void displayGraph();
    size_t num_vertices;
    size_t num_edges;
  private:
    unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> adjacency_list;
};

