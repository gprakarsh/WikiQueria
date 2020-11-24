#pragma once

#include <string>

struct Vertex{    
    // // // Member Functions // // //
    Vertex(size_t node_id, std::string page_name);
    bool operator==(const Vertex &other) const;
    bool operator<(const Vertex &other) const;
    // // // Member Variables // // // 
    size_t node_id_, degree_;
    std::string page_name_;
};