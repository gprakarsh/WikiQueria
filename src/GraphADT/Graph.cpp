#include "Graph.h"
#include "BFS.h"
#include "FullBFS.h"

#include <iostream>
#include <fstream>
#include <sstream> 
#include <algorithm>

using std::cout;
using std::endl;
using std::flush;
using std::min;
using std::string;


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
    std::string trash;
    int vertexCount = 0;
    while(verticesFile.good()){
        // Initialize a line of the file as a stream
        std::getline(verticesFile, line);
        std::stringstream line_stream(line);
        std::string page_name;
        std::string node_id_str;
        // Read up to the comma for the node_id
        std::getline(line_stream, node_id_str, ',');
        // Discard the first quote
        std::getline(line_stream, trash, '"');
        // Read up to the second quote for the page_name
        std::getline(line_stream, page_name, '"');
        // If we encountered a comment, continue; otherwise, insert a new vertex
        if (node_id_str[0] == '#' || node_id_str[0] == '"' || !node_id_str[0]) continue;
        size_t node_id = stoi(node_id_str);
        Vertex v(node_id, page_name);
        insertVertex(v);
        vertexCount++;
        cout << "\rVertices Loaded: " << vertexCount << flush;
    }
    cout<<endl;
};

void Graph::createEdges(const std::string & edgesFileName, size_t limit){     
    std::ifstream edgesFile(edgesFileName);
    if(!edgesFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line;
    size_t edgeCount = 0;
    while(edgesFile.good()){
        // Read a line in the edge file, and initialize it as a stream
        std::getline(edgesFile, line);
        std::stringstream line_stream(line);
        std::string from_node_id_str, to_node_id_str;
        // Extract the source vertex
        std::getline(line_stream, from_node_id_str, ' ');
        // Extract the ending vertex
        std::getline (line_stream, to_node_id_str);
        // If we read a hash, we encountered a comment; continue with next line
        if (from_node_id_str[0] == '#' || !from_node_id_str[0]) continue;
        size_t from_node_id = stoi(from_node_id_str);
        size_t to_node_id = stoi(to_node_id_str);
        // If each vertex exists, insert the edge into the graph
        if((vertices.find(from_node_id) != vertices.end())&&(vertices.find(to_node_id) != vertices.end())) {
            if (limit != static_cast<size_t>(-1) && edgeCount >= limit) break;
            insertEdge(vertices.at(from_node_id), vertices.at(to_node_id));
            edgeCount++;
            cout << "\rEdges Loaded: " << edgeCount << flush;
        }
    }
    cout<<endl;
};

void Graph::insertVertex(Vertex v){
    // std::cout << "Inserting " << v << "\n";
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

BFSTraversal Graph::getBFS(const Vertex& v) {
    return BFSTraversal(*this, v);
}

BFSTraversal Graph::getBFS(size_t id) {
    return BFSTraversal(*this, vertices.at(id));
}

FullBFS Graph::getFullBFS(const Vertex& v) {
    return FullBFS(*this, v);
}

FullBFS Graph::getFullBFS(size_t id) {
    return FullBFS(*this, vertices.at(id));
}

vector<Edge> Graph::getShortestPath(const Vertex start, const Vertex end) {
    vector<Edge> path; // Holds output path
    unordered_map<size_t, Edge> originEdge; // Holds edge from which we reached vertex
    originEdge[start.node_id_]; // Insert empty edge for the start node
    bool found = false;
    BFSTraversal searchBFS = getBFS(start);

    // Run BFS while keeping track of predecessors in originEdge
    for (auto it = searchBFS.begin(); it != searchBFS.end(); ++it) {
        originEdge.insert({(*it).node_id_, it.arrivalEdge()});
        if (*it == end) {
            found = true;
            break;
        }
    }

    // If found, reconstruct the path using originEdge
    if (found) {
        size_t last = end.node_id_;
        while (last != start.node_id_) {
            path.push_back(originEdge.at(last));
            last = originEdge.at(last).source_node_id_;
        }
        std::reverse(path.begin(), path.end());
    }
    
    return path;
}

vector<Edge> Graph::getLandmarkPath(const Vertex& source,const Vertex& destination,const Vertex& landmark) {
    vector<Edge> source_landmark;
    vector<Edge> landmark_destination;
    vector<Edge> combined;

    source_landmark = getShortestPath(source, landmark);
    landmark_destination = getShortestPath(landmark, destination);

    if(source_landmark.size() != 0 && landmark_destination.size() != 0){
        combined.insert(combined.begin(),source_landmark.begin(),source_landmark.end());
        combined.insert(combined.end(),landmark_destination.begin(),landmark_destination.end());
    }

    return combined;
}

void Graph::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = "images/" + title + ".dot";
    neatoFile.open(filename.c_str());

    if (!neatoFile.good())
        std::cerr << "\033[1;31m[Graph Error]\033[0m couldn't create " + filename + ".dot" << endl;

    neatoFile
        << "digraph G {\n";

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            size_t vertex1Text = it->first.node_id_;
            size_t vertex2Text = it2->first.node_id_;

            neatoFile << vertex1Text;
            neatoFile << " -> " ;
            neatoFile << vertex2Text;
            
            neatoFile<< ";\n";
        }
    }

    neatoFile << "}";
    neatoFile.close();
    string command = "dot -Tpng " + filename + " -o " + "images/" + title
                     + ".png";
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Output graph saved as images/" << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
    }

    string rmCommand = "rm -f " + filename + " 2> /dev/null";
    system(rmCommand.c_str());
}