#include <string>
#include <vector>

#include "Graph.h"
#include "BFS.h"

#include "catch.hpp"

Graph basicTestGraph() {
	Graph g = Graph();
	Vertex v0 = Vertex(0, "zero");
    Vertex v1 = Vertex(1, "one");
    Vertex v2 = Vertex(2, "two");
    Vertex v3 = Vertex(3, "three");

    g.insertVertex(v0);
    g.insertVertex(v1);
    g.insertVertex(v2);
    g.insertVertex(v3);
    
    g.insertEdge(v0, v1);
    g.insertEdge(v1, v2);
    g.insertEdge(v2, v3);
    g.insertEdge(v3, v0);

	return g;
}

TEST_CASE("Verify that these tests compile") {
	REQUIRE(true);
}

TEST_CASE("Verify that vertices and edges are properly inserted", "[GraphADT]") {
	Graph g = basicTestGraph();

	REQUIRE(g.num_vertices == 4);
	REQUIRE(g.num_edges == 4);
}

TEST_CASE("Verify that edgeExists queries work","[GraphADT]") {
	Vertex v0 = Vertex(0, "zero");
    Vertex v1 = Vertex(1, "one");
    Vertex v2 = Vertex(2, "two");
    Vertex v3 = Vertex(3, "three");
    Graph g = basicTestGraph();

	REQUIRE(g.edgeExists(v0, v1) == true);
	REQUIRE(g.edgeExists(v1, v1) == false);
	REQUIRE(g.edgeExists(v2, v3) == true);
}

TEST_CASE("Verify that vertexExists queries work", "[GraphADT]") {
	Vertex v0 = Vertex(0, "zero");
    Vertex v1 = Vertex(1, "one");
    Vertex v2 = Vertex(25, "anything");
    Graph g = basicTestGraph();

	REQUIRE(g.vertexExists(v0) == true);
	REQUIRE(g.vertexExists(v1) == true);
	REQUIRE(g.vertexExists(v2) == false);
}

TEST_CASE("Demonstrate how to use the incidentEdges and incidentVertices function.", "[GraphADT]") {
    Graph g = basicTestGraph();
	Vertex v0 = Vertex(0, "zero");
	for (auto& it : g.incidentEdges(v0)) {
        Edge incidentEdge = it; 
	}
    for(auto& it : g.incidentVertices(v0)){
        Vertex incidentVertex = it;
    }
	REQUIRE(true);
}

TEST_CASE("Verify that removeEdge function work as expected.", "[GraphADT]"){
    Graph g = basicTestGraph();
    Vertex v0(0, "zero");
    Vertex v1(1, "one");

    g.removeEdge(v0, v1);

    REQUIRE(g.num_edges == 3);
    REQUIRE(g.edgeExists(v0, v1) == false);

    g.removeEdge(v0, v1);       // this should not remove anything
    REQUIRE(g.num_edges == 3);  // num_edges should remain same for non-existent edge
}

TEST_CASE("Verify that removeVertex function work as expected.", "[GraphADT]"){
    Graph g = basicTestGraph();
    Vertex v0(0, "zero");

    g.removeVertex(v0);

    REQUIRE(g.num_vertices == 3);           // function should remove the Vertex
    REQUIRE(g.vertexExists(v0) == false);
    REQUIRE(g.num_edges == 2);              // function should remove all the vertex's Edges
}

TEST_CASE("Verify the BFS works as expected", "[BFS]") {
    Graph g = basicTestGraph();
    Vertex v0(0, "zero");
    BFSTraversal bfs = g.getBFS(v0);
    
    int count = 0;
    for (auto b : bfs) {
        CAPTURE(b);
        count++;
    }
    REQUIRE(count == 4);
}

TEST_CASE("Show that in a BFS, we know where we came from.", "[BFS]") {
    Graph g = basicTestGraph();
    Vertex v0(0, "zero");
    BFSTraversal bfs = g.getBFS(v0);
    int count;
    for (auto b : bfs) {
        CAPTURE(b);
        count++;
    }
    REQUIRE(count == 4);
}

TEST_CASE("Verify that loading data works") {
    Graph gIO = Graph("./tests/mock-data/Vertices.csv", "./tests/mock-data/Edges.txt");
}