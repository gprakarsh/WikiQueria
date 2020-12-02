#include <iostream>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "BFS.h"

// Uses Universal Addressing to help with visualizing the tree
// Every child has one more `.`, except for the root=0
// http://courses.ics.hawaii.edu/ReviewICS241/morea/trees/TreeTraversal-QA.pdf

Graph basicTree() {
    Graph g = Graph();
    Vertex v0 = Vertex(0, "0");
    Vertex v1 = Vertex(1, "1");
    Vertex v2 = Vertex(2, "2");
    Vertex v1_1 = Vertex(3, "1.1");
    Vertex v1_2 = Vertex(4, "1.2");
    Vertex v2_1 = Vertex(5, "2.1");
    Vertex v2_2 = Vertex(6, "2.2");
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
    return g;
}
int main(){
    Vertex v0 = Vertex(0, "zero");
    Vertex v1 = Vertex(1, "one");
    Vertex v2 = Vertex(2, "two");
    Vertex v3 = Vertex(3, "three");

    Graph g = Graph();

    g.insertVertex(v0);
    g.insertVertex(v1);
    g.insertVertex(v2);
    g.insertVertex(v3);
    
    g.insertEdge(v0, v1);
    g.insertEdge(v1, v1);
    g.insertEdge(v1, v2);
    g.insertEdge(v2, v3);
    g.insertEdge(v3, v0);

    g.displayGraph();

    Graph treeGraph = basicTree();
    std::cout << "Treelike structure\n";
    treeGraph.displayGraph();

    std::cout << "BFS Traversal from root='0':\n";

    for (auto v : treeGraph.getBFS(Vertex(0, "0"))) {
        std::cout << v << ", ";
    }
    std::cout << '\n';

    std::cout << "BFS Traversal from subroot='1':\n";

    for (auto v : treeGraph.getBFS(Vertex(1, "1"))) {
        std::cout << v << ", ";
    }
    std::cout << '\n';

    auto bfs = treeGraph.getBFS(Vertex(0, "0"));
    for (auto it = bfs.begin(); it != bfs.end(); ++it) {
        std::cout << *it << ", origin: " << it.arrivalEdge().source_node_id_ << '\n';
    }
    bfs = treeGraph.getBFS(Vertex(1, "1"));

    return 0;
};
