#pragma once
#include <iostream>
#include <list>

// size_t is not defined otherwise
// c++ y u do dis

struct Edge{
    Edge(size_t edge_number, size_t initial_node_id, size_t terminal_node_id);
    size_t edge_number_, initial_node_id_, terminal_node_id_;
    std::list<Edge>::iterator edgeInSrcVertex;
};

/*
    Iterator i
      v
a->b->c->d->e

std::erase(i)

a->b->d->e
*/