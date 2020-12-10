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
    // Default constructor, initializes an empty Graph
    Graph();
    
    // Constructor to initialize a graph from a given vertex file, edge file, and edge limit
    Graph(const std::string & verticesFileName, const std::string & EdgesFileName, size_t limit = -1);

    /* Basic GraphADT functions */
    void insertVertex(Vertex v);
    virtual void removeVertex(const Vertex& v);
    bool edgeExists(const Vertex& source,const Vertex& destination);
    bool vertexExists(const Vertex& v);
    void insertEdge(Vertex& source,Vertex& destination); 
    virtual void removeEdge(const Vertex& source,const Vertex& destination);
    vector<Vertex> incidentVertices(const Vertex& v) const;
    vector<Edge> incidentEdges(const Vertex& v) const;

    /* 
     * Methods related to target algorithms 
     */
    // Returns the edges required to traverse the shortest path
    vector<Edge> getShortestPath(const Vertex start, const Vertex end);

    // Returns BFS initialized from known vertex
    BFSTraversal getBFS(const Vertex& v);

    // Returns BFS initialized from vertex id
    BFSTraversal getBFS(size_t id);

    // Returns FullBFS initialized from known vertex
    FullBFS getFullBFS(const Vertex& v);

    // Returns BFS initialized from vertex id
    FullBFS getFullBFS(size_t id);

    // Displays the adjacency list for a graph
    virtual void displayGraph();

    // Returns the edges required to traverse the shortest path with a landmark
    vector<Edge> getLandmarkPath(const Vertex& source,const Vertex& destination,const Vertex& landmark);

    // Export image of graph as a PNG using graphviz
    void savePNG(std::string title) const;
    size_t num_vertices;
    size_t num_edges;
    unordered_map<size_t, Vertex> vertices;
    unordered_map<std::string, size_t> page_to_id;
  protected:
    unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> adjacency_list;
  private:
    // Helper methods for inputting files
    void createVertices(const std::string & verticesFileName);
    void createEdges(const std::string & edgesFileName, size_t limit);
};

