#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "BFS.h"
#include "FullBFS.h"

using FullIterator = FullBFS::FullIterator;
using Iterator = BFSTraversal::Iterator;
FullBFS::FullBFS(Graph& g, const Vertex& start)
    : BFSTraversal(g, start) { /* inherited */  }
 
FullIterator::FullIterator(FullBFS& traversal, bool finished)
    : Iterator(traversal, finished) { /* inherited */ }
    
FullIterator& FullIterator::operator++() {
    visited_.insert(**this);
    traversal_->addNext(*this);
    traversal_->pop(*this);
    if (traversal_->empty(*this)) {
        for (auto v : traversal_->g_->vertices) {
            if (!visited(v.second)) {
                equeue_.push(Edge());
                queue_.push(v.second);
                return *this;
            }
        }
        finished_ = true;
    }
    return *this;}

FullIterator FullBFS::begin() {
    return FullIterator(*this, false);
}

FullIterator FullBFS::end() {
    return FullIterator(*this, true);
}