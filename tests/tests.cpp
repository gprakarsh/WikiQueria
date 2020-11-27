#include <string>
#include <vector>

#include "Graph.h"
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

TEST_CASE("Verify that vertices and edges are properly inserted") {
	Graph g = basicTestGraph();

	REQUIRE(g.edgeList().size() == 4);
	REQUIRE(g.vertexMap().size() == 4);
}

TEST_CASE("Verify that areAdjacent queries work") {
	Vertex v0 = Vertex(0, "zero");
    Vertex v1 = Vertex(1, "one");
    Vertex v2 = Vertex(2, "two");
    Vertex v3 = Vertex(3, "three");
    Graph g = basicTestGraph();

	REQUIRE(g.areAdjacent(v0, v1) == true);
	REQUIRE(g.areAdjacent(v1, v1) == false);
	REQUIRE(g.areAdjacent(v2, v3) == true);
}

TEST_CASE("Demonstrate how to use the incidentEdges function.") {
    Graph g = basicTestGraph();
	Vertex v0 = Vertex(0, "zero");
	
	for (auto edgeItr : g.incidentEdges(v0)) {
		Edge e = *edgeItr;
		size_t vId = edgeItr->terminal_node_id_;
		Vertex retrievedVertex = g.vertexMap().at(vId);
	}

	REQUIRE(true);
}