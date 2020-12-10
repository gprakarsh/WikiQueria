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

// Wrapper class for a connected BFS Traversal
class BFSTraversal {
public:
    // Pointer to graph to traverse over
    Graph* g_;

    // Constructor
    BFSTraversal(Graph& g, const Vertex& start);


    class Iterator : std::iterator<std::forward_iterator_tag, Vertex> {
    public:
        // Constructor
        Iterator(BFSTraversal& traversal, bool finished);

        // Necessary operators for a forward iterator
        virtual Iterator& operator++();
        Vertex& operator*();
        bool operator!=(const Iterator& other) const;

        // Returns the edge by which the current vertex was reached
        Edge arrivalEdge() const;

        // Returns whether or not 
        bool visited(const Vertex& v) const;

        VertexQueue queue_;
        EdgeQueue equeue_;
        VisitedSet visited_;
    protected:
    
        // Pointer to the traversal that created this iterator
        BFSTraversal* traversal_;

        // Finished flag
        bool finished_ = true;
    };

    // Necessary iterator methods for range-based for loops
    Iterator begin();
    Iterator end();

    // Adds all of the upcoming nodes to the traversal to the iterator
    virtual void addNext(Iterator& it);

    // Removes the current vertex in an iterator
    virtual void pop(Iterator& it);

    // Get the current vertex in an iterator
    virtual Vertex& peek(Iterator& it) const;

    // Returns whether the iterator is depleted
    virtual bool empty(Iterator& it) const;
protected:
    Vertex start_;
};
