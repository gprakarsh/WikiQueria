#include "Vertex.h"

Vertex::Vertex(size_t node_id, std::string page_name){
    node_id_ = node_id;
    page_name_ = page_name;
    degree_ = 0;
};

bool Vertex::operator==(const Vertex& other) const{
    return (this->node_id_ == other.node_id_) && (this->page_name_ == other.page_name_);
}

bool Vertex::operator<(const Vertex& other) const{
    return (this->node_id_<other.node_id_);
}
