#include <iostream>
#include "BFS.h"

using Iterator = BFSTraversal::Iterator;
using FullIterator = FullBFS::FullIterator;

Iterator::Iterator(BFSTraversal& traversal, bool finished)
: traversal_{&traversal}, finished_{finished} {
    if (!finished_) {
        queue_.push(traversal.start_);
        equeue_.push(Edge());
    }
};

Iterator& Iterator::operator++() {
    visited_.insert(**this);
    traversal_->addNext(*this);
    traversal_->pop(*this);
    if (traversal_->empty(*this))
        finished_ = true;
    return *this;
};

Vertex& Iterator::operator*() {
    return queue_.front();
};

bool Iterator::operator!=(const Iterator& other) const {
    return finished_ != other.finished_;
};

bool Iterator::visited(const Vertex& v) const {
    return (visited_.find(v) != visited_.end());
}

Edge Iterator::arrivalEdge() const {
    return equeue_.front();
}

BFSTraversal::BFSTraversal(Graph& g, const Vertex& start)
    : g_{&g}, start_{start} { /* nothing */ };

Iterator BFSTraversal::begin() {
    return Iterator(*this, false);
};

Iterator BFSTraversal::end() {
    return Iterator(*this, true);
};

void BFSTraversal::addNext(Iterator& it) {
    for (Vertex& v : g_->incidentVertices(*it)) {
        if (!it.visited(v)) {
            it.visited_.insert(v);
            it.equeue_.push(Edge((*it).node_id_, v.node_id_));
            it.queue_.push(v);
        }
    }
};

void BFSTraversal::pop(Iterator& it) {
    it.queue_.pop();
    it.equeue_.pop();
};

Vertex& BFSTraversal::peek(Iterator& it) const {
    return it.queue_.front();
};

bool BFSTraversal::empty(Iterator& it) const {
    return it.queue_.empty();
};

// class FullBFS {
// protected:
//     Graph& g_;
//     Vertex start_;
// public:
//     FullBFS(Graph& g, const Vertex& start);
//     class Iterator : std::iterator<std::forward_iterator_tag, Vertex> {
//     public:
//         Iterator(Vertex start, Graph& g, bool depleted);
//         BFSTraversal::Iterator current_;
//         VisitedSet visited_;
//     };
//     virtual Iterator begin();
//     virtual Iterator end();
// };

FullBFS::FullBFS(Graph& g, const Vertex& start)
    : g_{g}, start_{start} { /* nothing */ };

FullIterator::FullIterator(Vertex start, Graph& g, bool depleted)
    : curr_vertex_{start}, g_{g}, current_{g_.getBFS(start)}, current_iterator_{current_.begin()}, depleted_{depleted} {
        /* nothing */
    if (!depleted) {
        visited_.insert(*current_iterator_);
    }
};

FullIterator& FullIterator::operator++() {
    // Go through the iterator while we've already visited the vertex
    while (visited_.find(*current_iterator_) != visited_.end() && current_iterator_ != current_.end()) {
        ++current_iterator_;
    }
    // In the case we deplete, try to rejuvenate with a new BFS.
    if (!(current_iterator_ != current_.end())) {
        for (auto tuple : g_.vertices) {
            if (visited_.find(tuple.second) == visited_.end()) {
                curr_vertex_ = tuple.second;
                current_ = g_.getBFS(curr_vertex_);
                current_iterator_ = current_.begin();
                return *this;
            }
        }
        depleted_ = true;
        return *this;
    } 
    visited_.insert(*current_iterator_);
    return *this;
}

bool FullIterator::operator!=(const FullIterator& other) const{
    return other.depleted_ != depleted_;
}
Vertex& FullIterator::operator*() {
    return *current_iterator_;
}

FullIterator FullBFS::begin() {
    return FullIterator(start_, g_, false);
};

FullIterator FullBFS::end() {
    return FullIterator(start_, g_, true);
};