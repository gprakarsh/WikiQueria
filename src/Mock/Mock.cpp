#include "Mock.h"
#include <string>

// Uses something like Universal Addressing to help with visualizing the tree
// Every child has one more `.`, except for the root=0
// http://courses.ics.hawaii.edu/ReviewICS241/morea/trees/TreeTraversal-QA.pdf
void insertBasicTree(Graph& g, size_t start) {
    std::string sep = ".";
    Vertex v0 = Vertex(start, std::to_string(start));
    Vertex v1 = Vertex(start+1, std::to_string(start) + sep + std::to_string(1));
    Vertex v2 = Vertex(start+2, std::to_string(start) + sep + std::to_string(2));
    Vertex v1_1 = Vertex(start+3, std::to_string(start) + sep + std::to_string(1) + sep + std::to_string(1));
    Vertex v1_2 = Vertex(start+4, std::to_string(start) + sep + std::to_string(1) + sep + std::to_string(2));
    Vertex v2_1 = Vertex(start+5, std::to_string(start) + sep + std::to_string(2) + sep + std::to_string(1));
    Vertex v2_2 = Vertex(start+6, std::to_string(start) + sep + std::to_string(2) + sep + std::to_string(2));
    g.insertVertex(v0);
    g.insertVertex(v1);
    g.insertVertex(v2);
    g.insertVertex(v1_1);
    g.insertVertex(v1_2);
    g.insertVertex(v2_1);
    g.insertVertex(v2_2);

    g.insertEdge(v0, v1);
    g.insertEdge(v0, v2);
    g.insertEdge(v1, v1_1);
    g.insertEdge(v1, v1_2);
    g.insertEdge(v2, v2_1);
    g.insertEdge(v2, v2_2);
}

void insertBasicCycle(Graph& g, size_t start) {
	
    Vertex v0 = Vertex(start, std::to_string(start));
    Vertex v1 = Vertex(start+1, std::to_string(start+1));
    Vertex v2 = Vertex(start+2, std::to_string(start+2));
    Vertex v3 = Vertex(start+3, std::to_string(start+3));

    g.insertVertex(v0);
    g.insertVertex(v1);
    g.insertVertex(v2);
    g.insertVertex(v3);
    
    g.insertEdge(v0, v1);
    g.insertEdge(v1, v2);
    g.insertEdge(v2, v3);
    g.insertEdge(v3, v0);

}