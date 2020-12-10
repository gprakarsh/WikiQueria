#pragma once

#include "Graph.h"

#include<iostream>

class SCCGraph : public Graph {
    public:
        // Reference to original graph
        Graph& original;

        // Constructor requires reference, since SCCGraph does not make sense without a source graph
        SCCGraph(Graph& g);

        // Returns whether or not `end` is reachable from `start`
        bool pathExists(const Vertex& start, const Vertex& end);

        // Displays the DAG of strongly connected components induced by the original graph
        void displayGraph();

        // Displays the representative node for each strongly connected component
        void displayRepNodes();

        // Displays all SCCs, with their size and their member vertices
        void displaySCCs(std::ostream& os);
        
        // Get the shortest path, but use SCC to query reachability first
        vector<Edge> getShortestPathFast(const Vertex& start, const Vertex& end);

        // Get the landmark path, but use SCC to query reachability first
        vector<Edge> getLandmarkPathFast(const Vertex& source, const Vertex& destination, const Vertex& landmark);
        
        // Unsupported functions!
        void removeVertex(const Vertex& v);
        void removeEdge(const Vertex& source,const Vertex& destination);
    private:
        // Helper function to process SCCs as vertices and edges in the graph
        void loadSCCsAsGraph();

        // Placeholder function for unsupported function
        void not_supported();

        // Helper functions for Tarjan's SCC algorithm
        void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]);
        void condense_graph_dfs();
        void condense_graph_dfs_util(int u, bool* visited);
        
        // Member variables
        size_t num_SCCs;
        size_t num_SCC_edges;
        vector<size_t> rep_node_ids;
        unordered_map<size_t, size_t> rep_node_finder;
        unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> comp_adj_list;
};