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


TEST_CASE("To check if landmark path works or not", "[LandmarkPath]"){
    Vertex a(0, "0");
    Vertex landmark (1, "1");
    Vertex b(2,"2");

    Graph g;

    g.insertEdge(a,b);
    g.insertEdge(a,landmark);
    g.insertEdge(landmark,b);

    vector<Edge> ans = g.Landmarkpath(a,b,landmark);

    REQUIRE( ans.empty() == false); //checking if our concatenation of the two vectors is working or not
    REQUIRE( ans[0].source_node_id_ == 0);
    REQUIRE( ans[1].source_node_id_ == 1);
    REQUIRE( ans[1].destination_node_id_ == 2);

}
