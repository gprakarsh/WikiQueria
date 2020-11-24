#pragma once

#include "Vertex.h"

struct Edge{
    // // // Member functions // // //
    Edge(const Vertex& initial,const Vertex& terminal, int weight = 1);
    // // // Member variables // // //
    int weight_;
    const Vertex& initial_;
    const Vertex& terminal_;
};

