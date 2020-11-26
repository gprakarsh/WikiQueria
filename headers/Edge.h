#pragma once
#include <iostream>
#include <list>

struct Edge;
using EdgeListIterator = std::list<Edge>::iterator;
using VertexBucketIterator = std::list<EdgeListIterator>::iterator;

struct Edge{
    Edge(size_t edge_number, size_t initial_node_id, size_t terminal_node_id);
    size_t edge_number_, initial_node_id_, terminal_node_id_;
    VertexBucketIterator edgeInSrcVertex;
};

/*
    Iterator i
      v
a->b->c->d->e

std::erase(i)

a->b->d->e
*/