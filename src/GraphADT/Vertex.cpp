#include "Vertex.h"

GraphADT::Vertex::Vertex(size_t node_id, std::string page_name){
    node_id_ = node_id;
    page_name_ = page_name;
    degree_ = 0;
};

bool GraphADT::Vertex::operator==(const Vertex& other) const{
    return (node_id_ == other.node_id_) && (page_name_ == other.page_name_);
}

bool GraphADT::Vertex::operator<(const Vertex& other) const{
    return (node_id_<other.node_id_);
}
