#include <iostream>
#include <stdlib.h>

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
int main(int argc, char* argv[]){
    // Vertex v0 = Vertex(0, "zero");
    // Vertex v1 = Vertex(1, "one");
    // Vertex v2 = Vertex(2, "two");
    // Vertex v3 = Vertex(3, "three");

    // Graph g = Graph();

    // g.insertVertex(v0);
    // g.insertVertex(v1);
    // g.insertVertex(v2);
    // g.insertVertex(v3);
    
    // g.insertEdge(v0, v1);
    // g.insertEdge(v1, v1);
    // g.insertEdge(v1, v2);
    // g.insertEdge(v2, v3);
    // g.insertEdge(v3, v0);

    // g.displayGraph();

    // Graph treeGraph = basicTree();
    // std::cout << "Treelike structure\n";
    // treeGraph.displayGraph();

    // std::cout << "BFS Traversal from root='0':\n";

    // for (auto v : treeGraph.getBFS(Vertex(0, "0"))) {
    //     std::cout << v << ", ";
    // }
    // std::cout << '\n';

    // std::cout << "BFS Traversal from subroot='1':\n";

    // for (auto v : treeGraph.getBFS(Vertex(1, "1"))) {
    //     std::cout << v << ", ";
    // }
    // std::cout << '\n';

    // auto bfs = treeGraph.getBFS(Vertex(0, "0"));
    // for (auto it = bfs.begin(); it != bfs.end(); ++it) {
    //     std::cout << *it; 
    //     if(!it.arrivalEdge().isEmpty){
    //         std::cout<<", origin: " << it.arrivalEdge().source_node_id_ << '\n';
    //     } else {
    //         std::cout<<" (root)"<<std::endl;
    //     }
    // }
    // bfs = treeGraph.getBFS(Vertex(1, "1"));

    ////////////Preprocessing//////////////
    std::cout<<"Started preprocessing"<<std::endl;
    std::string verticesFile = argv[1];
    std::string edgesFile = argv[2];
    { Graph g = Graph(verticesFile, edgesFile, atoi(argv[3])); }
    return 0;
    Graph pGraph = Graph();
    std::cout<<"Preprocessing successful"<<std::endl;
    
    if (argc >= 4){

        //////////////////User-Interface/////////////////////////
        if (std::string(argv[3]) == "--interactive" || std::string(argv[3]) == "-i") {
            bool exit = false;
            while(!exit){
                std::cout<<"What would you like to do?"<<std::endl;
                std::cout<<"1) See full graph"<<std::endl;
                std::cout<<"2) Clear Screen"<<std::endl;
                //Add more options here
                std::cout<<"Type the corresponding number to the desired option or anything else to exit"<<std::endl;
                int option;
                std::cin>>option;
                if(option==1){
                    pGraph.displayGraph();
                }else if(option==2){
                    system("clear");
                }else{
                    exit = true;
                }
            }
        }
    }
    //////////////////////////////////////

    return 0;
};
