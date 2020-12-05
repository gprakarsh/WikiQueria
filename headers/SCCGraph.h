#pragma once

#include "Graph.h"

#include<iostream>

class SCCGraph : public Graph {
    public:
        SCCGraph(const std::string & verticesFileName, const std::string & edgesFileName);
        void insertVertex(Vertex v){not_supported();};
        void removeVertex(const Vertex& v){not_supported();};
        void edgeExists(const Vertex& source,const Vertex& destination){not_supported();};
        bool vertexExists(const Vertex& v){not_supported();};
        void insertEdge(Vertex& source,Vertex& destination){not_supported();}; 
        void removeEdge(const Vertex& source,const Vertex& destination){not_supported();};
        void displayGraph();
        void displayRepNodes();
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