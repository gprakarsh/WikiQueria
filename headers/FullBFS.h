#pragma once
#include <iterator>
#include <queue>
#include <unordered_set>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "BFS.h"

using VisitedSet = std::unordered_set<Vertex, VertexHashFunction>;
using VertexQueue = std::queue<Vertex>;
using EdgeQueue = std::queue<Edge>;

// Wrapper class for a complete BFS Traversal
class FullBFS : public BFSTraversal {
public:
    // Constructor
    FullBFS(Graph& g, const Vertex& start);

    // Inherited class representing the iterator
    class FullIterator : public BFSTraversal::Iterator {
    public:
        FullIterator(FullBFS& traversal, bool finished);

        // Override default ++ behavior to allow for disconnected vertices to be visited
        FullIterator& operator++();
    private:
        std::unordered_set<size_t> unvisited_;
    };
    virtual FullIterator begin();
    virtual FullIterator end();
};