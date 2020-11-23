#pragma once

#include <string>



struct Vertex{
        
    Vertex(size_t node_id, std::string page_name);

    // // // Member Functions // // //

    bool operator==(const Vertex &other) const {
    
    };

    bool operator<(const Vertex &other) const {

    };

    // // // Member Variables // // // 

    size_t node_id_;
    std::string page_name_;


};