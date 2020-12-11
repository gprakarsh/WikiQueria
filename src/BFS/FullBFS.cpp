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
    : Iterator(traversal, finished) { 
    for (auto v : traversal_->g_->vertices)
        unvisited_.insert(v.second.node_id_);
}
    
FullIterator& FullIterator::operator++() {
    visited_.insert(**this);
    unvisited_.erase((**this).node_id_);
    traversal_->addNext(*this);
    traversal_->pop(*this);

    if (traversal_->empty(*this)) {
        // Different from BFSTraversal::Iterator
        // Iterate over vertices until an unvisited one is encountered

        if (unvisited_.size()) {
            equeue_.push(Edge());
            queue_.push(traversal_->g_->vertices.at(*(unvisited_.begin())));
        } else {
            finished_ = true;
        }
        // Otherwise, return a depleted iterator
    }
    return *this;
}

FullIterator FullBFS::begin() {
    return FullIterator(*this, false);
}

FullIterator FullBFS::end() {
    return FullIterator(*this, true);
}