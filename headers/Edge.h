#pragma once
#include <iostream> 

// size_t is not defined otherwise
// c++ y u do dis

struct Edge{
    Edge(size_t edge_number, size_t initial_node_id, size_t terminal_node_id);
    size_t edge_number_, initial_node_id_, terminal_node_id_;
    // std::list<Edge>::iterator pointerToEdgeInEdgeList;
    
};

/*
    Iterator i
      v

Edge* ePtr; (points to C)

[vertex] -> <iteratorsToEdgeList>

<edgelist> {Edges}

Edge {
    edge_number_, init_node_id_, terminal_node_id;
    iteratorToVertexBucket i;
}

BucketEdgeNode {
    Iterator edgeInEdgelist;
}



a->b->c->d->e

std::erase(i)

a->b->d->e


Edgelist: Edges
Edge
*/
