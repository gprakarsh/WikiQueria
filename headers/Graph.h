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
class FullBFS;

class Graph{
  public:
    Graph();
    Graph(const std::string & verticesFileName, const std::string & EdgesFileName, size_t limit = -1);
    void insertVertex(Vertex v);
    virtual void removeVertex(const Vertex& v);
    bool edgeExists(const Vertex& source,const Vertex& destination);
    bool vertexExists(const Vertex& v);
    void insertEdge(Vertex& source,Vertex& destination); 
    virtual void removeEdge(const Vertex& source,const Vertex& destination);
    vector<Vertex> incidentVertices(const Vertex& v) const;
    vector<Edge> incidentEdges(const Vertex& v) const;
    vector<Edge> getShortestPath(const Vertex start, const Vertex end);
    BFSTraversal getBFS(const Vertex& v);
    BFSTraversal getBFS(size_t id);
    FullBFS getFullBFS(const Vertex& v);
    FullBFS getFullBFS(size_t id);
    virtual void displayGraph();
    vector<Edge> getLandmarkPath(const Vertex& source,const Vertex& destination,const Vertex& landmark);
    void savePNG(std::string title)const;
    size_t num_vertices;
    size_t num_edges;
    unordered_map<size_t, Vertex> vertices;
    unordered_map<std::string, size_t> page_to_id;
  protected:
    unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> adjacency_list;
  private:
    void createVertices(const std::string & verticesFileName);
    void createEdges(const std::string & edgesFileName, size_t limit);
};

