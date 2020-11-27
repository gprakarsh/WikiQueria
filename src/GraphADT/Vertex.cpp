#include "Vertex.h"

Vertex::Vertex(size_t node_id, std::string page_name){
    node_id_ = node_id;
    page_name_ = page_name;
    degree_ = 0;
};

bool Vertex::operator==(const Vertex& other) const{
    return (node_id_ == other.node_id_) && (page_name_ == other.page_name_);
}

bool Vertex::operator<(const Vertex& other) const{
    return (node_id_<other.node_id_);
}

size_t Vertex::hash() const {
    return node_id_;
}

