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

class FullBFS : public BFSTraversal {
public:
    FullBFS(Graph& g, const Vertex& start);
    class FullIterator : public BFSTraversal::Iterator {
    public:
        FullIterator(FullBFS& traversal, bool finished);
        FullIterator& operator++();
        // bool operator!=(const FullIterator& other) const;
        // bool visited(const Vertex& v) const;
    };
    virtual FullIterator begin();
    virtual FullIterator end();
};