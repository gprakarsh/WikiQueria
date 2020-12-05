#pragma once

#include "Graph.h"

#include<iostream>

class SCCGraph : public Graph {
    public:
        SCCGraph(const std::string & verticesFileName, const std::string & edgesFileName);
        // void displayGraph();
        void displayRepNodes();
    private:
        size_t num_SCCs;
        size_t num_SCC_edges;
        void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]);
        void condense_graph_dfs();
        void condense_graph_dfs_util(int u, bool* visited, unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> comp_adj_list);
        vector<size_t> rep_node_ids;
        unordered_map<size_t, size_t> rep_node_finder;
        // unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> comp_adj_list; 
};