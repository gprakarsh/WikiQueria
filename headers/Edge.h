#pragma once

#include "Vertex.h"

#include <iostream>
#include <list>


struct Edge{
    Edge();
    Edge(size_t source_node_id, size_t destination_node_id);
    Edge(const Edge& edge);
    bool isEmpty();
    size_t source_node_id_;
    size_t destination_node_id_;
};

