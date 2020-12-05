#include "Vertex.h"

Vertex::Vertex(size_t node_id, std::string page_name){
    node_id_ = node_id;
    page_name_ = page_name;
    degree_ = 0;
};

Vertex::Vertex(const Vertex& v){
    node_id_ = v.node_id_;
    page_name_ = v.page_name_;
    degree_ = v.degree_;
};

bool Vertex::operator==(const Vertex& other) const{
    return (node_id_ == other.node_id_) && (page_name_ == other.page_name_);
}

bool Vertex::operator<(const Vertex& other) const{
    return (node_id_<other.node_id_);
}
std::ostream &operator<<(std::ostream& os, const Vertex& v) {
    return os << "V(" << v.node_id_<< ", " << v.page_name_ << ")";
}
