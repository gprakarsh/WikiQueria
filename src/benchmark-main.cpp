#include <iostream>
#include <stdlib.h>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "BFS.h"
#include "FullBFS.h"
#include "Mock.h"
#include "SCCGraph.h"
#include "ArgumentParser.h"

void demo() {
    Vertex v0 = Vertex(0, "0");
    Vertex v1 = Vertex(1, "1");
    Vertex v2 = Vertex(2, "2");
    Vertex v3 = Vertex(3, "3");

    Graph g;
    insertBasicCycle(g, 0);
    std::cout << "Cyclical structure\n";
    g.displayGraph();

    Graph treeGraph;
    insertBasicTree(treeGraph, 0);
    std::cout << "Treelike structure\n";
    treeGraph.displayGraph();
    std::cout << "BFS Traversal of cycle from root\n";
    for (auto v : g.getBFS(Vertex(0, "0"))) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
    std::cout << "BFS Traversal of tree from root='0':\n";

    for (auto v : treeGraph.getBFS(Vertex(0, "0"))) {
        std::cout << v << ", ";
    }
    std::cout << '\n';

    std::cout << "BFS Traversal of tree from subroot='0.1':\n";

    for (auto v : treeGraph.getBFS(Vertex(1, "0.1"))) {
        std::cout << v << ", ";
    }
    std::cout << '\n';

    std::cout << "Demonstration of BFS and obtaining predecessors.\n";
    auto bfs = treeGraph.getBFS(Vertex(0, "0"));
    for (auto it = bfs.begin(); it != bfs.end(); ++it) {
        std::cout << *it; 
        if(!it.arrivalEdge().isEmpty()){
            std::cout<<", origin: " << it.arrivalEdge().source_node_id_ << '\n';
        } else {
            std::cout<<" (root)"<<std::endl;
        }
    }   
    bfs = treeGraph.getBFS(Vertex(1, "1"));
    auto p = treeGraph.getShortestPath(Vertex(0, "0"), Vertex(1, "1"));
    auto q = g.getShortestPath(Vertex(3, "3"), Vertex(0, "0"));
    auto nonexistent = treeGraph.getShortestPath(Vertex(1, "0.1"), Vertex(0, "0"));
}

int main(int argc, char* argv[]){
    ////////////Preprocessing//////////////
    ArgumentParser parser = ArgumentParser("benchmark");
    parser.addFlag("-i", "Launch interactively");
    parser.addFlag("-x", "Do not launch interactively and only load the graph (benchmarking)");
    parser.addOption("-c", "EDGES", "Specify the number of edges to load");
    if (argc < 2) {
        demo();
        std::cout << "Wikipedia Page Query Benchmark Tool\n";
        std::cout << "===================\n";
        parser.display();
        return 1;
    }
    parser.processArgs(argc, argv);
    size_t limit;
    if (parser.getOption("-c") != "") {
        limit = stoi(parser.getOption("-c"));
    }
    else limit = -1;

    std::string verticesFile = parser.getVertexFile();
    std::string edgesFile = parser.getEdgeFile();

    if (parser.getFlag("-x")) {
        std::cout << "Benchmarking only.\n";
        Graph g = Graph(verticesFile, edgesFile, limit);
        SCCGraph pGraph = SCCGraph(g);
        return 0;
    }
    //////////////////////////////////////

    return 0;
};
