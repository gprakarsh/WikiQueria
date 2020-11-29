#include "Graph.h"

#include <iostream>

using std::cout;
using std::endl;


Graph::Graph(){
    //do nothing
};

void Graph::insertVertex(const Vertex& v){
    //remove v if v already exists
    adjacency_list[v] = unordered_map<Vertex, Edge, VertexHashFunction>();
};

void Graph::removeVertex(const Vertex& v){
    
    // Target: O(deg(v))
    // Current: O(n) (n is the number of vertices)

    if (adjacency_list.find(v) != adjacency_list.end())
    {
        adjacency_list.erase(v);
        for(auto i : adjacency_list)
        {
            if (i.second.find(v)!=i.second.end())
            {
                i.second.erase(v);
            }
        }
    }

    
};  

bool Graph::edgeExists(const Vertex& source,const Vertex& destination){
    //should also check if both vertices exist
    if(vertexExists(source) && vertexExists(destination)){
        if(adjacency_list[source].find(destination) == adjacency_list[source].end()){
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
};

bool Graph::vertexExists(const Vertex& v){
    if(adjacency_list.find(v) == adjacency_list.end()){
        return false;
    } else {
        return true;
    }
}

void Graph::insertEdge(Vertex& source,Vertex& destination){
    if(!vertexExists(source)){
        insertVertex(source);
    }
    if(!vertexExists(destination)){
        insertVertex(destination);
    }
    if(source == destination){  //self loops are not allowed
        return;
    }
    if(!edgeExists(source, destination)){
        Edge newEdge(source.node_id_, destination.node_id_);
        adjacency_list[source].insert({destination, newEdge}); 
    }

};

void Graph::removeEdge(const Vertex& source,const Vertex& destination){
    if(edgeExists(source, destination)){
       adjacency_list[source].erase(destination); 
    }
};

vector<Vertex> Graph::incidentVertices(const Vertex& v){
    vector<Vertex> incidentVertices_;
    for(auto i : adjacency_list[v]){
        incidentVertices_.push_back(i.first);
    }
    return incidentVertices_;    
};

vector<Edge> Graph::incidentEdges(const Vertex& v){
    vector<Edge> incidentEdges_;
    for(auto i : adjacency_list[v]){
        incidentEdges_.push_back(i.second);
    }
    return incidentEdges_;    
};

void Graph::displayGraph(){
    for(auto i : adjacency_list){
        Vertex a = i.first;
        cout<<a.node_id_<<" : ";
        for(auto j : adjacency_list[a]){
            Vertex b = j.first;
            cout<<a.node_id_<<"->"<<b.node_id_<<" ";
        }
        cout<<endl;
    }
};