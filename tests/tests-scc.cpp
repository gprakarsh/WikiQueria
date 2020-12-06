#include <string>
#include <vector>
#include <iostream>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "BFS.h"
#include "FullBFS.h"
#include "SCCGraph.h"
#include "Mock.h"

#include "catch.hpp"



TEST_CASE("getShortestPathFast returns the same result as getShortestPath if a path exists") {
    Graph g;insertBasicCycle(g, 0);
    SCCGraph sG = SCCGraph(g);
    Vertex v0(0, "0");
    Vertex v3(3, "3");
    auto path = sG.getShortestPathFast(v0, v3);
    for (auto p : path) {
        std::cout << p.source_node_id_ << "->" << p.destination_node_id_ << '\n';
    }
    REQUIRE(path.size() == 3);

}

TEST_CASE("getShortestPathFast returns the same result as getShortestPath if a path doesn't exist") {
    Graph g;insertBasicCycle(g, 0);
    SCCGraph sG = SCCGraph(g);
    Vertex v0(0, "0");
    Vertex v3(3, "3");
    g.removeEdge(v3, v0);
    auto path = sG.getShortestPathFast(v3, v0);
    REQUIRE(path.size() == 0);
}

TEST_CASE("Querying an SCCGraph via strings works by reading from file", "[UI]") {
    Graph g("./tests/mock-data/scc-examples/scc-names-rand.csv", "./tests/mock-data/scc-examples/scc-edges-rand.txt");
    SCCGraph sIO(g);
    std::string start = "Hequfegoho a";
    std::string end = "Gitoxugesido";
    auto path = g.getShortestPath(g.vertices.at(g.page_to_id.at(start)), g.vertices.at(g.page_to_id.at(end)));
    for (auto p : path) {
        std::cout << p.source_node_id_ << "->" << p.destination_node_id_ << '\n';
    }
    REQUIRE(path.size() > 0);
}

TEST_CASE("Querying an SCCGraph via size_t works by reading from file", "[SCC]") {
    Graph g("./tests/mock-data/scc-examples/scc-names-rand.csv", "./tests/mock-data/scc-examples/scc-edges-rand.txt");
    size_t start = 0;
    size_t end = 32;
    auto path = g.getShortestPath(g.vertices.at(start), g.vertices.at(end));
    for (auto p : path) {
        std::cout << p.source_node_id_ << "->" << p.destination_node_id_ << '\n';
    }
    REQUIRE(path.size() > 0);
}

TEST_CASE("getShortestPath on the original via size_t works by reading from file", "[SCC]") {
    Graph g("./tests/mock-data/scc-examples/scc-names-rand.csv", "./tests/mock-data/scc-examples/scc-edges-rand.txt");
    SCCGraph s(g);
    size_t start = 0;
    size_t end = 32;
    auto path = s.original.getShortestPath(s.original.vertices.at(start), s.original.vertices.at(end));
    for (auto p : path) {
        std::cout << p.source_node_id_ << "->" << p.destination_node_id_ << '\n';
    }
    REQUIRE(path.size() > 0);
}
