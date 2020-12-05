#include "SCCGraph.h"

#include <iostream>
#include <algorithm> 

using std::cout;
using std::endl;
using std::min;

#define UNVISITED -1

SCCGraph::SCCGraph(const std::string & verticesFileName, const std::string & edgesFileName) : Graph(verticesFileName, edgesFileName){
    num_SCC_edges = 0;
    num_SCCs = 0;
    int *disc = new int[num_vertices]; 
    int *low = new int[num_vertices]; 
    bool *stackMember = new bool[num_vertices]; 
    stack<int> *st = new stack<int>(); 

    size_t i = 0;
    while(i<num_vertices){
        disc[i] = UNVISITED; 
        low[i] = UNVISITED; 
        stackMember[i] = false; 
        i++;
    }

    i = 0;
    while(i < num_vertices){
        if (disc[i] == UNVISITED){
            SCCUtil(i, disc, low, st, stackMember);
        } 
        i++;
    }

    condense_graph_dfs();
};

void SCCGraph::SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]){
    static int time = 0; 

    disc[u] = low[u] = ++time;
    st->push(u); 
    stackMember[u] = true; 
    
    vector<Vertex> adjVertices = incidentVertices(vertices.at(u));

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
        rep_node_ids.push_back(vertices.at(u).node_id_);
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
    unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> comp_adj_list;

    int i = 0;
    while(i <(int) rep_node_ids.size()){
        comp_adj_list[vertices.at(rep_node_ids[i])] = unordered_map<Vertex, Edge, VertexHashFunction>();
        i++;
    }
    bool* visited = new bool[num_vertices];
    i = 0;
    while(i < (int) num_vertices){
        visited[i] = false;
        i++;
    };

    i=0;
    while(i < (int) num_vertices){
        if (visited[i] == false){
            condense_graph_dfs_util(i, visited, comp_adj_list);
        }
        i++;
    }
    adjacency_list = comp_adj_list;
};

void SCCGraph::condense_graph_dfs_util(int start, bool* visited, unordered_map<Vertex, unordered_map<Vertex, Edge, VertexHashFunction>, VertexHashFunction> comp_adj_list){
    visited[start] = true;
    vector<Vertex> adjVertices = incidentVertices(vertices.at(start));
    for(Vertex& currVertex : adjVertices){
        size_t currVertexRep = rep_node_finder[currVertex.node_id_];
        size_t startRep = rep_node_finder[vertices.at(start).node_id_];
        if(currVertexRep == startRep){
            continue;
        } else {
            Edge newEdge(vertices.at(startRep).node_id_, vertices.at(currVertexRep).node_id_);
            comp_adj_list[vertices.at(startRep)][vertices.at(currVertexRep)] = newEdge;
            num_SCC_edges++; 
        }
        if(visited[currVertex.node_id_] == false){
            condense_graph_dfs_util(currVertex.node_id_, visited, comp_adj_list);
        }
    }
}

// void SCCGraph::displayGraph(){
//     cout<< "Number of SCCs : "<<rep_node_ids.size()<<endl;
//     cout<< "Number of SCC Edges : "<<num_SCC_edges<<endl;
//     for(auto i : comp_adj_list){
//         Vertex a = i.first;
//         cout<<a.node_id_<<" : ";
//         for(auto j : adjacency_list[a]){
//             Vertex b = j.first;
//             cout<<a.node_id_<<"->"<<b.node_id_<<" ";
//             // cout<<b.node_id_<<" ";
//         }
//         cout<<endl;
//     }
// }

void SCCGraph::displayRepNodes(){
    for(auto i : rep_node_ids){
        cout<< i << " ";
    }
    std::cout<<std::endl;
};
