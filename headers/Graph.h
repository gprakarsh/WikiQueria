#pragma once

// // // Files // // //

#include "Vertex.h"
#include "Edge.h"

// // // Modules // // //

#include <unordered_map>
#include <list>
#include <vector>
#include <stack>



using std::unordered_map;
using std::list;
using std::vector;
using std::stack;

class BFSTraversal;

class Graph{
  public:
    Graph();
    Graph(const std::string & verticesFileName, const std::string & edgesFileName);
    void insertVertex(Vertex v);
    void removeVertex(const Vertex& v);
    bool edgeExists(const Vertex& source,const Vertex& destination);
    bool vertexExists(const Vertex& v);
    void insertEdge(Vertex& source,Vertex& destination); // Use Disjoint Sets + Path Compression to check for good query
    void removeEdge(const Vertex& source,const Vertex& destination);
    vector<Vertex> incidentVertices(const Vertex& v) const;
    vector<Edge> incidentEdges(const Vertex& v) const;
    BFSTraversal getBFS(const Vertex& v);
    void displayGraph();
    // void SCC();
    size_t num_vertices;
    size_t num_edges;
  protected:
    unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> adjacency_list;
    unordered_map<size_t, Vertex> vertices;
  private:
    // void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]);
    void createVertices(const std::string & verticesFileName);
    void createEdges(const std::string & edgesFileName);
    // vector<size_t> rep_node_ids; // rep_node_ids[0] gives the rep_node_id of the Vertex with node_id 0;  
};

