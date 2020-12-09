#include <iostream>
#include <stdlib.h>
#include <chrono>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "BFS.h"
#include "FullBFS.h"
#include "Mock.h"
#include "SCCGraph.h"
#include "ArgumentParser.h"

using myclock = std::chrono::high_resolution_clock;

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
    parser.addFlag("--bfs", "Set benchmarking to BFS (sweeps: number of BFS steps)");
    parser.addFlag("--scc", "Set benchmarking to SCC (sweeps: number of edges in original graph, ignores -e)");
    parser.addOption("-e", "EDGES", "Specify the number of edges to load");
    parser.addOption("-m", "SAMPLES", "Specify the number of samples to run");
    parser.addOption("--step", "STEP_SIZE", "(sweeping) Specify the step of a sweep");
    parser.addOption("--from", "STEP_START", "(sweeping) Specify the number of samples to run");
    parser.addOption("--count", "STEP_COUNT", "(sweeping) Number of sweeping steps");
    if (argc < 2 || !parser.processArgs(argc, argv)) {
        demo();
        std::cout << "Wikipedia Page Link Graph Runtime Benchmark Tool\n";
        std::cout << "Note: I output CSVs to stderr! Redirect my output with 2> in the shell to extract it.\n";
        std::cout << "===================\n";
        parser.display();
        std::cout << "===================\n";
        std::cout << "Note: If you want to benchmark, you have to specify --step, --from, and --count. See the README for example usage.\n";
        return 1;
    }

    size_t limit = -1;
    if (!parser.getOption("-e").empty()) {
        limit = stoi(parser.getOption("-e"));
    }

    std::string verticesFile = parser.getVertexFile();
    std::string edgesFile = parser.getEdgeFile();

    int samples = 10;
    if (!parser.getOption("-m").empty()) {
        samples = stoi(parser.getOption("-m"));
    }
    std::cout << "Number of samples: " << samples << '\n';
    typedef std::chrono::high_resolution_clock myClock;
    typedef std::chrono::duration<double, std::milli> dsec;

    double avg = 0;
    if (parser.getFlag("--bfs")) {
        Graph g = Graph(verticesFile, edgesFile, limit);
        int num_vertices = stoi(parser.getOption("--from"));
        int increment = stoi(parser.getOption("--step"));
        int entries = stoi(parser.getOption("--count"));
        for (int run = 0; run < entries; run++) {
            for (int i = 0; i < samples; i++) {
                FullBFS bfs = g.getFullBFS(0);
                auto t0 = myClock::now();
                int count = 0;
                // for (auto it = bfs.begin(); it != bfs.end(); ++it) {
                for (auto it = bfs.begin(); it != bfs.end(); ++it) {
                    count++;
                    if (count == num_vertices) break;
                }
                auto t1 = myClock::now();
                dsec elapsed = t1 - t0;
                avg += elapsed.count();
            }
            avg = avg / samples;
            std::cout << "BFS: " << avg << " milliseconds\n";
            std::cerr << num_vertices << ',' << avg << '\n';
            num_vertices += increment;
        }
    } else if (parser.getFlag("--scc")) {
        int num_edges = stoi(parser.getOption("--from"));
        int increment = stoi(parser.getOption("--step"));
        int entries = stoi(parser.getOption("--count"));
        for (int run = 0; run < entries; run++) {
            Graph g = Graph(verticesFile, edgesFile, num_edges);
            for (int i = 0; i < samples; i++) {
                auto t0 = myClock::now();
                /* Do timeable action here*/
                SCCGraph s = SCCGraph(g);
                /* End timeable action */
                auto t1 = myClock::now();
                dsec elapsed = t1 - t0;
                avg += elapsed.count();
            }
            avg = avg / samples;
            std::cout << "SCC: " << avg << " milliseconds\n";
            std::cerr << num_edges << ',' << avg << '\n';
            num_edges += increment;
        }
    }
    return 0;
};
