#include "Edge.h"


Edge::Edge(size_t source_node_id,size_t destination_node_id){
    source_node_id_ = source_node_id;
    destination_node_id_ = destination_node_id;
    isEmpty = false;
};

Edge::Edge(const Edge& edge){
    source_node_id_ = edge.source_node_id_;
    destination_node_id_ = edge.destination_node_id_;
    isEmpty = edge.isEmpty;
};

Edge::Edge(){
    source_node_id_ = -1;
    destination_node_id_ = -1;
    isEmpty = true;
};

