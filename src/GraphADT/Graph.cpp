#include "Graph.h"
#include "BFS.h"

#include <iostream>
#include <fstream>
#include <sstream> 
#include <algorithm>

using std::cout;
using std::endl;
using std::flush;
using std::min;


Graph::Graph(){
    num_vertices = 0;
    assert (num_vertices == 0);
    num_edges = 0;
};

Graph::Graph(const std::string & verticesFileName, const std::string & edgesFileName, size_t limit)
    : Graph() {
    createVertices(verticesFileName);
    createEdges(edgesFileName, limit);
};

void Graph::createVertices(const std::string & verticesFileName){
    std::ifstream verticesFile(verticesFileName);
    assert (num_vertices == 0);
    if(!verticesFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line;
    int vertexCount = 0;
    while(verticesFile.good()){
        std::getline(verticesFile, line);
        std::stringstream line_stream(line);
        std::string page_name;
        std::string node_id_str;
        // if (lineCount % 20000 == 0) {cout << "."; cout.flush(); lineCount = 1;}
        std::getline(line_stream, node_id_str, ',');
        std::getline (line_stream, page_name);
        if (node_id_str[0] == '#' || node_id_str[0] == '"' || !node_id_str[0]) continue;
        size_t node_id = stoi(node_id_str);
        Vertex v(node_id, page_name);
        insertVertex(v);
        cout << "\rVertices Loaded: " << vertexCount << flush;
        vertexCount++;
    }
    cout<<endl;
};

void Graph::createEdges(const std::string & edgesFileName, size_t limit){     
    std::ifstream edgesFile(edgesFileName);
    if(!edgesFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line;
    size_t edgeCount = 0;
    while(edgesFile.good()){
        std::getline(edgesFile, line);
        std::stringstream line_stream(line);
        std::string from_node_id_str, to_node_id_str; 
        // if (lineCount % 40000 == 0) {cout << "."; cout.flush(); lineCount = 0;}
        std::getline(line_stream, from_node_id_str, ' ');
        std::getline (line_stream, to_node_id_str);
        if (from_node_id_str[0] == '#' || !from_node_id_str[0]) continue;
        size_t from_node_id = stoi(from_node_id_str);
        size_t to_node_id = stoi(to_node_id_str);
        if((vertices.find(from_node_id) != vertices.end())&&(vertices.find(to_node_id) != vertices.end())) {
            if (limit != static_cast<size_t>(-1) && edgeCount > limit) break;
            insertEdge(vertices.at(from_node_id), vertices.at(to_node_id));
            edgeCount++;
            cout << "\rEdges Loaded: " << edgeCount << flush;
        }
    }
    cout<<endl;
};

void Graph::insertVertex(Vertex v){
    adjacency_list[v] = unordered_map<Vertex, Edge, VertexHashFunction>();
    vertices.insert({v.node_id_, v});
    page_to_id.insert({v.page_name_, v.node_id_});
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

// void Graph::SCC(){
//     int *disc = new int[num_vertices]; 
//     int *low = new int[num_vertices]; 
//     bool *stackMember = new bool[num_vertices]; 
//     stack<int> *st = new stack<int>(); 

//     size_t i = 0;
//     while(i<num_vertices){
//         disc[i] = UNVISITED; 
//         low[i] = UNVISITED; 
//         stackMember[i] = false; 
//         i++;
//     }

//     i = 0;
//     while(i < num_vertices){
//         if (disc[i] == UNVISITED){
//             SCCUtil(i, disc, low, st, stackMember);
//         } 
//         i++;
//     }

// }

// void Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]){
    
//     static int time = 0; 

//     disc[u] = low[u] = ++time;
//     st->push(u); 
//     stackMember[u] = true; 
    
//     vector<Vertex> adjVertices = incidentVertices(vertices.at(u));

//     int i = 0;
//     for(i = 0; i < (int) adjVertices.size(); i++){
//         int v = adjVertices[i].node_id_;
//         if(disc[v] == UNVISITED){
//             SCCUtil(v, disc, low, st, stackMember);
//             low[u] = min(low[u], low[v]);
//         } else if(stackMember[v] == true){
//             low[u] = min(low[u], low[v]);
//         }
//     }

//     i = 0;
//     if(low[u] == disc[u]){
//         while(st->top() != u){
//             i = st->top();
//             cout << i << " ";
//             stackMember[i] = false; 
//             st->pop(); 
//         }
//         i = st->top(); 
//         cout << i << endl; 
//         stackMember[i] = false; 
//         st->pop(); 
//     }
// };

BFSTraversal Graph::getBFS(const Vertex& v) {
    return BFSTraversal(*this, v);
}

BFSTraversal Graph::getBFS(size_t id) {
    return BFSTraversal(*this, vertices.at(id));
}

FullBFS Graph::getFullBFS(const Vertex& v) {
    return FullBFS(*this, v);
}


vector<Edge> Graph::getShortestPath(const Vertex start, const Vertex end) {
    vector<Edge> path;
    unordered_map<size_t, Edge> originEdge;
    originEdge[start.node_id_];
    bool found = false;
    BFSTraversal searchBFS = getBFS(start);
    for (auto it = searchBFS.begin(); it != searchBFS.end(); ++it) {
        originEdge.insert({(*it).node_id_, it.arrivalEdge()});
        if (*it == end) {
            found = true;
            break;
        }
    }

    if (!found) return path;
    else {
        size_t last = end.node_id_;
        while (last != start.node_id_) {
            path.push_back(originEdge.at(last));
            last = originEdge.at(last).source_node_id_;
        }
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}
