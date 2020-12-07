#pragma once

#include "Graph.h"

#include<iostream>

class SCCGraph : public Graph {
    public:
        Graph& original;
        // SCCGraph(const std::string & verticesFileName, const std::string & edgesFileName, size_t limit = -1);
        SCCGraph(Graph& g);
        void removeVertex(const Vertex& v);
        void removeEdge(const Vertex& source,const Vertex& destination);
        bool pathExists(const Vertex& start, const Vertex& end);
        void loadSCCsAsGraph();
        void displayGraph();
        void displayRepNodes();
        void displaySCCs();
        vector<Edge> getShortestPathFast(const Vertex& start, const Vertex& end);
    private:
        void not_supported();
        void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]);
        void condense_graph_dfs();
        void condense_graph_dfs_util(int u, bool* visited);
        size_t num_SCCs;
        size_t num_SCC_edges;
        vector<size_t> rep_node_ids;
        unordered_map<size_t, size_t> rep_node_finder;
        unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> comp_adj_list;
};