#include "BFS.h"

using Iterator = BFSTraversal::Iterator;

Iterator::Iterator(BFSTraversal& traversal, bool finished)
: traversal_{&traversal}, finished_{finished} {
    if (!finished_) {
        queue_.push(traversal.start_);
        equeue_.push(Edge(-1, -1));
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
}
