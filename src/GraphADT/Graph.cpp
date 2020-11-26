#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

#include <iostream>
#include <unordered_map>
#include <list> 

Graph::Graph(){
    edgeNum = 0;
};

void Graph::insertVertex(Vertex& v){
    std::list<EdgeListIterator> newList;
    AdjList.insert(std::make_pair(v.hash(), newList));
    vertexMap.insert(std::make_pair(v.hash(), v));
};

void Graph::removeVertex(Vertex& v){
        
};

bool Graph::areAdjacent(Vertex& v1, Vertex& v2){

};

void Graph::insertEdge(Vertex& v1, Vertex& v2){
    if (!(v1.hash() == v2.hash())) {
        Edge newEdge = Edge(edgeNum, v1.hash(), v2.hash());
        EdgeList.push_front(newEdge);
        AdjList.at(v1.hash()).push_back(EdgeList.begin());
        v1.degree_++;
        // AdjList->at(&v2)->push_back(*newEdge);
        // v2.degree_++;
    }
};

void Graph::removeEdge(Vertex& v1, Vertex& v2){

};

std::list<EdgeListIterator>& Graph::incidentEdges(Vertex& v){
    return AdjList.at(v.hash());
};

void Graph::displayGraph(){
    for(auto i : AdjList){
        size_t vId = i.first;
        std::cout<<vId<<" : ";
        for(auto currEdge : i.second){
            std::cout<< currEdge->initial_node_id_ << "=>"  << currEdge->terminal_node_id_ <<" ";
        }
        std::cout<<std::endl;
    }
};
