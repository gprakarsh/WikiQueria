#pragma once
#include <iterator>
#include <queue>
#include <unordered_set>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

using VisitedSet = std::unordered_set<Vertex, VertexHashFunction>;
using VertexQueue = std::queue<Vertex>;
using EdgeQueue = std::queue<Edge>;
// class BFSTraversal;

class BFSTraversal {
protected:
    Graph* g_;
    Vertex start_;
public:
    BFSTraversal(Graph& g, const Vertex& start);
    class Iterator : std::iterator<std::forward_iterator_tag, Vertex> {
    public:
        Iterator(BFSTraversal& traversal, bool finished);
        Iterator& operator++();
        Vertex& operator*();
        bool operator!=(const Iterator& other) const;
        Edge arrivalEdge() const;
        VertexQueue queue_;
        EdgeQueue equeue_;
        VisitedSet visited_;
        bool visited(const Vertex& v) const;
    private:
        BFSTraversal* traversal_;
        bool finished_ = true;
    };
    virtual Iterator begin();
    virtual Iterator end();
    virtual void addNext(Iterator& it);
    virtual void pop(Iterator& it);
    virtual Vertex& peek(Iterator& it) const;
    virtual bool empty(Iterator& it) const;
};
