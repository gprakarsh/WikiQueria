#pragma once

#include <string>

    struct Vertex{    
        Vertex(size_t node_id, std::string page_name);
        bool operator==(const Vertex &other) const; 
        bool operator<(const Vertex &other) const;
        size_t node_id_, degree_;
        std::string page_name_;
    };

class VertexHashFunction { 
    public: 
        size_t operator()(const Vertex& v) const { 
            return  v.node_id_;
        } 
};