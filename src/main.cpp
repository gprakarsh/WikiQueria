#include <iostream>
#include <stdlib.h>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "BFS.h"
#include "FullBFS.h"
#include "Mock.h"
#include "SCCGraph.h"


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
    if (argc == 1) {
        demo();
        std::cout << "===================\n";
        std::cout << "Usage: ./finalproj VERTEXFILE EDGEFILE [-i|-x] EDGELIMIT" << '\n';
        std::cout << "-i : Launch interactively." << '\n';
        std::cout << "-x : Do not launch interactively and only load the graph (benchmarking)." << '\n';
        return 1;
    }
    ////////////Preprocessing//////////////
    std::string verticesFile = argv[1];
    std::string edgesFile = argv[2];

    if (argc >= 4){
        if (std::string(argv[3]) == "-x") {
                std::cout << "Benchmarking only.\n";
                Graph g = Graph(verticesFile, edgesFile, atoi(argv[4]));
                SCCGraph pGraph = SCCGraph(g);
                return 0;
        }
        //////////////////User-Interface/////////////////////////
        else if (std::string(argv[3]) == "--interactive" || std::string(argv[3]) == "-i") {
            std::cout<<"Started preprocessing"<<std::endl;
            size_t limit;
            if (argc >= 5) 
                limit = atoi(argv[4]);
            else
                limit = -1;
            Graph g = Graph(verticesFile, edgesFile, limit);
            SCCGraph pGraph = SCCGraph(g);
            std::cout<<"Preprocessing successful"<<std::endl;
            bool exit = false;
            while(!exit){
                std::cout<<"What would you like to do?"<<std::endl;
                std::cout<<"1) See full graph"<<std::endl;
                std::cout<<"2) Print SCCs"<<std::endl;
                std::cout<<"3) Print Full BFS"<<std::endl;
                std::cout<<"4) Find shortest path"<<std::endl;
                std::cout<<"5) Clear Screen"<<std::endl;
                //Add more options here
                std::cout<<"Type the corresponding number to the desired option or anything else to exit"<<std::endl;
                int option;
                std::cin>>option;
                if (option == 1){
                    pGraph.original.displayGraph();
                } else if (option == 2){
                    std::cout<<"Following are the Strongly Connected Components:"<<std::endl;
                    pGraph.displayRepNodes();
                } else if (option == 3){
                    for (auto v : pGraph.getFullBFS(0)) {
                        std::cout << v << std::endl;
                    }
                } else if (option == 4){

                    std::string start_page, end_page;

                    std::cout << "Enter start page: ";
                    std::getline(std::cin >> std::ws, start_page);

                    std::cout << "Enter end page: ";
                    std::getline(std::cin >> std::ws, end_page);

                    std::cout << "Starting Page : " << start_page << "\n";
                    std::cout << "End Page : " << end_page << "\n";

                    Graph gr = pGraph.original;
                    size_t sp_id = gr.page_to_id.at(start_page);
                    size_t ep_id = gr.page_to_id.at(end_page);
                    vector<Edge> shortestPathEdges = gr.getShortestPath(gr.vertices.at(sp_id), gr.vertices.at(ep_id));

                    std::cout << "No. of edges in shortest path : " << shortestPathEdges.size() << std::endl;
                    
                    for(size_t i = 0; i < shortestPathEdges.size(); i++){
                        std::string next_page = gr.vertices.at(shortestPathEdges[i].destination_node_id_).page_name_;
                        std::cout << next_page << std::endl;
                    }
                    std::cout << gr.num_vertices << "\n";
                } else if (option == 5) {
                    system("clear");
                } else {
                    exit = true;
                }
            }
        }
    } 
    //////////////////////////////////////

    return 0;
};
