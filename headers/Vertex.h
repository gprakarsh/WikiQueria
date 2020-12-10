#pragma once

#include <string>
#include <fstream>

struct Vertex{    
    Vertex(size_t node_id, std::string page_name);
    Vertex(const Vertex& v);
    bool operator==(const Vertex &other) const; 
    bool operator<(const Vertex &other) const;
    size_t node_id_, degree_;
    std::string page_name_;
};

// Function used to allow unordered_map usage
class VertexHashFunction { 
    public: 
        size_t operator()(const Vertex& v) const { 
            return  v.node_id_;
        } 
};

// Source: https://stackoverflow.com/questions/2981836/how-can-i-use-cout-myclass
std::ostream &operator<<(std::ostream& os, const Vertex& v);
