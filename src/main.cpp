#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

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

    return 0;
};
