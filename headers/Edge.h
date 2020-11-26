#pragma once

#include "Graph.h"

namespace GraphADT{
    struct Edge{
        Edge(size_t edge_number, size_t initial_node_id, size_t terminal_node_id);
        size_t edge_number_, initial_node_id_, terminal_node_id_;
    };
}

