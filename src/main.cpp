#include <iostream>
#include <stdlib.h>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "BFS.h"
#include "FullBFS.h"
#include "Mock.h"
#include "SCCGraph.h"

int main(int argc, char* argv[]){
    ////////////Preprocessing//////////////
    if (argc == 1) {
        std::cout << "Wikipedia Page Query Tool\n";
        std::cout << "===================\n";
        std::cout << "Usage: ./finalproj VERTEXFILE EDGEFILE [EDGELIMIT]" << '\n';
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
        else {
            std::cout<<"Started preprocessing"<<std::endl;
            size_t limit;
            if (argc >= 4) 
                limit = atoi(argv[3]);
            else
                limit = -1;
            Graph g = Graph(verticesFile, edgesFile, limit);
            SCCGraph pGraph = SCCGraph(g);
            std::cout<<"Preprocessing successful"<<std::endl;
            bool exit = false;
            while(!exit){
                std::cout << "What would you like to do?"<<std::endl;
                std::cout << "1) See full graph"<<std::endl;
                std::cout << "2) See compressed graph (compressed using SCCs)"<<std::endl;
                std::cout << "3) Print SCCs"<<std::endl;
                std::cout << "4) Print Full BFS"<<std::endl;
                std::cout << "5) Find shortest path"<<std::endl;
                std::cout << "6) Find shortest path through landmark"<<std::endl;
                std::cout << "7) Clear Screen"<<std::endl;
                //Add more options here
                std::cout << "Type the corresponding number to the desired option or anything else to exit"<<std::endl;
                int option;
                std::cin >> option;
                if (option == 1){
                    pGraph.original.displayGraph();
                } else if (option == 2){
                    pGraph.displayGraph();
                } else if (option == 3){
                    std::cout<<"Following are the Strongly Connected Components:"<<std::endl;
                    pGraph.displaySCCs();
                } else if (option == 4){
                    for (auto v : pGraph.getFullBFS(0)) {
                        std::cout << v << std::endl;
                    }
                } else if (option == 5){

                    std::string start_page, end_page;

                    std::cout << "Enter start page: ";
                    std::getline(std::cin >> std::ws, start_page);

                    std::cout << "Enter end page: ";
                    std::getline(std::cin >> std::ws, end_page);

                    std::cout << "Starting Page : " << start_page << "\n";
                    std::cout << "End Page : " << end_page << "\n";

                    Graph& gr = pGraph.original;
                    size_t sp_id = gr.page_to_id.at(start_page);
                    size_t ep_id = gr.page_to_id.at(end_page);
                    vector<Edge> shortestPathEdges = pGraph.getShortestPathFast(gr.vertices.at(sp_id), gr.vertices.at(ep_id));

                    std::cout << "No. of edges in shortest path : " << shortestPathEdges.size() << std::endl;
                    
                    for(size_t i = 0; i < shortestPathEdges.size(); i++){
                        std::string next_page = gr.vertices.at(shortestPathEdges[i].destination_node_id_).page_name_;
                        std::cout << next_page << std::endl;
                    }
                    
                } else if (option == 6){

                    std::string start_page, landmark_page, end_page;

                    std::cout << "Enter start page: ";
                    std::getline(std::cin >> std::ws, start_page);
                    
                    std::cout << "Enter landmark page: ";
                    std::getline(std::cin >> std::ws, landmark_page);

                    std::cout << "Enter end page: ";
                    std::getline(std::cin >> std::ws, end_page);

                    std::cout << "\n" <<"Starting Page : " << start_page << "\n";
                    std::cout << "Landmark Page : " << landmark_page << "\n";
                    std::cout << "End Page : " << end_page << "\n" << "\n";

                    Graph& gr = pGraph.original;
                    size_t sp_id = gr.page_to_id.at(start_page);
                    size_t lp_id = gr.page_to_id.at(landmark_page);
                    size_t ep_id = gr.page_to_id.at(end_page);
                    vector<Edge> shortestPathEdges = pGraph.original.Landmarkpath(gr.vertices.at(sp_id), gr.vertices.at(ep_id), gr.vertices.at(lp_id));

                    std::cout << "No. of edges in shortest path through Landmark: " << shortestPathEdges.size() << std::endl;
                    
                    for(size_t i = 0; i < shortestPathEdges.size(); i++){
                        std::string next_page = gr.vertices.at(shortestPathEdges[i].destination_node_id_).page_name_;
                        std::cout << next_page << std::endl;
                    }

                } else if (option == 7) {
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
