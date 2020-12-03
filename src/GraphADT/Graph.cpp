#include "Graph.h"
#include "BFS.h"

#include <iostream>
#include <fstream>
#include <sstream> 

using std::cout;
using std::endl;


Graph::Graph(){
    num_vertices = 0;
    num_edges = 0;
};

Graph::Graph(const std::string & verticesFileName, const std::string & edgesFileName){
    createVertices(verticesFileName);
    createEdges(edgesFileName);
};

void Graph::createVertices(const std::string & verticesFileName){

    std::ifstream verticesFile(verticesFileName);

    if(!verticesFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line;
    int lineCount = 0;

    while(verticesFile.good()){
        std::getline(verticesFile, line); 
        std::stringstream line_stream(line);
        std::string page_name;
        std::string node_id_str;
        if(lineCount > 0){
            std::getline(line_stream, node_id_str, ',');
            std::getline (line_stream, page_name);
            int node_id = stoi(node_id_str);
            Vertex v(node_id, page_name);
            insertVertex(v);
        }
        lineCount++;
    }
};

void Graph::createEdges(const std::string & edgesFileName){     //this function needs fixing
    std::ifstream edgesFile(edgesFileName);

    if(!edgesFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line;
    int lineCount = 0;

    while(edgesFile.good()){
        std::getline(edgesFile, line); 
        std::stringstream line_stream(line);
        std::string from_node_id_str, to_node_id_str; 
        if(lineCount > 0){
            std::getline(line_stream, from_node_id_str, ' ');
            std::getline (line_stream, to_node_id_str);
            size_t from_node_id = stoi(from_node_id_str);
            size_t to_node_id = stoi(to_node_id_str);
            if((vertices.find(from_node_id) != vertices.end())&&(vertices.find(to_node_id) != vertices.end())){
                cout<<vertices[from_node_id]->node_id_<<" "<<vertices[to_node_id]->node_id_<<endl;
            }
            // cout<<from_node_id<<" "<<to_node_id<<endl;
        }
        lineCount++;
    }
};

void Graph::insertVertex(Vertex v){
    //remove v if v already exists
    adjacency_list[v] = unordered_map<Vertex, Edge, VertexHashFunction>();
    // vertices[v.node_id_] = &v;
    num_vertices++;
};

void Graph::removeVertex(const Vertex& v){
    

    if (adjacency_list.find(v) != adjacency_list.end())
    {
        num_edges -= adjacency_list[v].size();
        adjacency_list.erase(v);
        for(auto i : adjacency_list)
        {
            if (i.second.find(v)!=i.second.end())
            {
                i.second.erase(v);
                num_edges --;
            }
        }
    }
    num_vertices--;
    
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
        num_edges++; 
    }
};

void Graph::removeEdge(const Vertex& source,const Vertex& destination){
    if(edgeExists(source, destination)){
       adjacency_list[source].erase(destination);
       num_edges--; 
    }
};

vector<Vertex> Graph::incidentVertices(const Vertex& v) const {
    vector<Vertex> incidentVertices_;
    for(auto i : adjacency_list.at(v)){
        incidentVertices_.push_back(i.first);
    }
    return incidentVertices_;    
};

vector<Edge> Graph::incidentEdges(const Vertex& v) const {
    vector<Edge> incidentEdges_;
    for(auto i : adjacency_list.at(v)){
        incidentEdges_.push_back(i.second);
    }
    return incidentEdges_;    
};

// Helper function to display the graph
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

BFSTraversal Graph::getBFS(const Vertex& v) {
    return BFSTraversal(*this, v);
}