#include "SCCGraph.h"

#include <iostream>
#include <algorithm> 

using std::cout;
using std::endl;
using std::min;

#define UNVISITED -1

SCCGraph::SCCGraph(Graph& g) : 
    original{g}{
    
    num_SCC_edges = 0;
    num_SCCs = 0;
    int *disc = new int[original.num_vertices]; 
    int *low = new int[original.num_vertices]; 
    bool *stackMember = new bool[original.num_vertices]; 
    stack<int> *st = new stack<int>(); 

    size_t i = 0;
    while(i<original.num_vertices){
        disc[i] = UNVISITED; 
        low[i] = UNVISITED; 
        stackMember[i] = false; 
        i++;
    }

    i = 0;
    while(i < original.num_vertices){
        if (disc[i] == UNVISITED){
            SCCUtil(i, disc, low, st, stackMember);
        } 
        i++;
    }
    delete[] disc;
    delete[] low;
    delete[] stackMember;
    delete st;
    condense_graph_dfs();
    loadSCCsAsGraph();
};

void SCCGraph::SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]){
    static int time = 0; 

    disc[u] = low[u] = ++time;
    st->push(u); 
    stackMember[u] = true; 
    
    vector<Vertex> adjVertices = original.incidentVertices(original.vertices.at(u));

    int i = 0;
    for(i = 0; i < (int) adjVertices.size(); i++){
        int v = adjVertices[i].node_id_;
        if(disc[v] == UNVISITED){
            SCCUtil(v, disc, low, st, stackMember);
            low[u] = min(low[u], low[v]);
        } else if(stackMember[v] == true){
            low[u] = min(low[u], low[v]);
        }
    }

    int currEl = 0;
    if(low[u] == disc[u]){
        rep_node_ids.push_back(original.vertices.at(u).node_id_);
        while(st->top() != u){
            currEl = st->top();
            // cout << currEl << " ";
            rep_node_finder[currEl] = u; 
            stackMember[currEl] = false; 
            st->pop(); 
        }
        currEl = st->top(); 
        // cout << currEl << endl; 
        rep_node_finder[currEl] = u; 
        stackMember[currEl] = false; 
        st->pop(); 
    }
};

void SCCGraph::condense_graph_dfs(){
    
    int i = 0;
    while(i <(int) rep_node_ids.size()){
        comp_adj_list[original.vertices.at(rep_node_ids[i])] = unordered_map<Vertex, Edge, VertexHashFunction>();
        i++;
    }
    bool* visited = new bool[original.num_vertices];
    i = 0;
    while(i < (int) original.num_vertices){
        visited[i] = false;
        i++;
    };

    i=0;
    while(i < (int) original.num_vertices){
        if (visited[i] == false){
            condense_graph_dfs_util(i, visited);
        }
        i++;
    }
    delete[] visited;
};

void SCCGraph::condense_graph_dfs_util(int start, bool* visited){
    visited[start] = true;
    vector<Vertex> adjVertices = original.incidentVertices(original.vertices.at(start));
    for(Vertex& currVertex : adjVertices){
        size_t currVertexRep = rep_node_finder[currVertex.node_id_];
        size_t startRep = rep_node_finder[original.vertices.at(start).node_id_];
        if(currVertexRep == startRep){
            continue;
        } else {
            Edge newEdge(original.vertices.at(startRep).node_id_, original.vertices.at(currVertexRep).node_id_);
            comp_adj_list[original.vertices.at(startRep)][original.vertices.at(currVertexRep)] = newEdge;
            num_SCC_edges++; 
        }
        if(visited[currVertex.node_id_] == false){
            condense_graph_dfs_util(currVertex.node_id_, visited);
        }
    }
}

void SCCGraph::loadSCCsAsGraph() {
    for (auto i : comp_adj_list) {
        insertVertex(i.first);
    }
    for (auto v : comp_adj_list) {
        for (auto adj : v.second) {
            Vertex dest = adj.first;
            Vertex source = v.first;
            insertEdge(source, dest);
        }
    }
}

void SCCGraph::displayGraph(){
    cout<< "Number of SCCs : "<<rep_node_ids.size()<<endl;
    cout<< "Number of SCC Edges : "<<num_SCC_edges<<endl;
    Graph::displayGraph();
}

void SCCGraph::displayRepNodes(){
    for(auto i : rep_node_ids){
        cout<< i << " ";
    }
    std::cout<<std::endl;
};

void SCCGraph::not_supported(){
    cout<<"Function not supported in SCC Graph"<<endl;
}
void SCCGraph::removeVertex(const Vertex& v) {
    (void)v; not_supported();
};

void SCCGraph::removeEdge(const Vertex& source,const Vertex& destination) {
    (void)source; (void)destination; not_supported();
};

bool SCCGraph::pathExists(const Vertex& start, const Vertex& end) {
    size_t parent_start = rep_node_finder.at(start.node_id_);
    size_t parent_end = rep_node_finder.at(end.node_id_);
    if (parent_start == parent_end) return true;
    else return (getShortestPath(vertices.at(parent_start), vertices.at(parent_end)).size() > 0);
};

vector<Edge> SCCGraph::getShortestPathFast(const Vertex& start, const Vertex& end) {
    vector<Edge> emptyPath;
    if(pathExists(start, end)){
        return original.getShortestPath(start, end);
    };
    return emptyPath;
}
