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

TEST_CASE("Verify connected BFS works as expected (cycle)", "[bfs]") {
    Graph g;
    insertBasicCycle(g, 0);
    Vertex v0(0, "0");
    BFSTraversal bfs = g.getBFS(v0);
    
    int count = 0;
    for (auto b : bfs) {
        CAPTURE(b);
        count++;
    }
    REQUIRE(count == 4);
}

TEST_CASE("Verify connected BFS works as expected (tree)", "[bfs]") {
    Graph g;
    insertBasicTree(g, 0);
    Vertex v0(0, "0");
    BFSTraversal bfs = g.getBFS(v0);
    
    int count = 0;
    for (auto b : bfs) {
        CAPTURE(b);
        count++;
    }
    REQUIRE(count == 7);
}

TEST_CASE("Because SCCGraphs are Graphs, a SCCGraph is traversable and correctly produces the acyclic graph", "[bfs]") {
    Graph gIO("./tests/mock-data/scc-examples/scc-names-hand.csv", "./tests/mock-data/scc-examples/scc-edges-hand.txt");
    SCCGraph sIO = SCCGraph(gIO);
    BFSTraversal bfs = sIO.getBFS(0);
    int count{};
    for (auto it = bfs.begin(); it != bfs.end(); ++it) {
        std::cout << *it << ", ";
        count++;
    }
    REQUIRE(count == 4);
}

TEST_CASE("Path exists queries using SCCGraphs works", "[bfs][scc]") {
    Graph gIO("./tests/mock-data/scc-examples/scc-names-hand.csv", "./tests/mock-data/scc-examples/scc-edges-hand.txt");
    SCCGraph sIO = SCCGraph(gIO);
    BFSTraversal bfs = sIO.getBFS(0);
    Vertex v0(0,"Page 0");
    Vertex v1(1,"Page 1");
    Vertex v2(2,"Page 2");
    Vertex v3(3,"Page 3");
    Vertex v4(4,"Page 4");
    Vertex v5(5,"Page 5");
    CHECK(sIO.pathExists(v0, v1) == true);
    CHECK(sIO.pathExists(v0, v2) == true);
    CHECK(sIO.pathExists(v0, v3) == true);
    CHECK(sIO.pathExists(v3, v0) == false);
    CHECK(sIO.pathExists(v0, v5) == true);
}

TEST_CASE("Making sure the full (disconnected) BFS works, one cycle of length 4", "[bfs]") {
    Graph g;insertBasicCycle(g, 0);
    Vertex v0(0, "0");
    int count{};
    for (auto v : g.getFullBFS(v0)) {
        count++;
    }
    REQUIRE(count == 4);
}

TEST_CASE("Making sure the full (disconnected) BFS works, three disjoint cycles of length 4 each", "[bfs]") {
    Graph g;insertBasicCycle(g, 0);
    insertBasicCycle(g, 4);
    insertBasicCycle(g, 8);
    insertBasicCycle(g, 17);
    Vertex v0(0, "0");
    int count{};
    for (auto v : g.getFullBFS(v0)) {
        count++;
    }
    REQUIRE(count == 16);
}

TEST_CASE("BFS Shortest Path returns correct path if path exists (cycle)", "[bfs]") {
    Graph g;insertBasicCycle(g, 0);
    Vertex v0(0, "0");
    Vertex v3(3, "3");
    auto path = g.getShortestPath(v0, v3);
    for (auto p : path) {
        std::cout << p.source_node_id_ << "->" << p.destination_node_id_ << '\n';
    }
    REQUIRE(path.size() == 3);
}

TEST_CASE("BFS Shortest Path returns correct path if path exists (tree)", "[bfs]") {
    Graph g;insertBasicTree(g, 0);
    Vertex v0(0, "0");
    Vertex v6(6, "0.2.2");
    auto path = g.getShortestPath(v0, v6);
    for (auto p : path) {
        std::cout << p.source_node_id_ << "->" << p.destination_node_id_ << '\n';
    }
    REQUIRE(path.size() == 2);

}

TEST_CASE("BFS Shortest Path returns nothing if path does not exist", "[bfs]") {
    Graph g;insertBasicCycle(g, 0);
    Vertex v0(0, "0");
    Vertex v3(3, "3");
    g.removeEdge(v3, v0);
    auto path = g.getShortestPath(v3, v0);
    REQUIRE(path.size() == 0);
}

