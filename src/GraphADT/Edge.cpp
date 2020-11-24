#include "Edge.h"

Edge::Edge(const Vertex& initial,const Vertex& terminal, int weight = 1){
    initial_ = initial;
    terminal_ = terminal;
    weight_ = weight; 
}