#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

#include <iostream>
#include <unordered_map>
#include <list> 

Graph::Graph(){
    AdjList = new std::unordered_map<Vertex*, std::list<Edge>*>;
    edgeNum = 0;
};

void Graph::insertVertex(Vertex& v){
    auto newList = new std::list<Edge>;
    AdjList->insert(std::make_pair(&v, newList));
};

void Graph::removeVertex(Vertex& v){
        
};

bool Graph::areAdjacent(Vertex& v1, Vertex& v2){

};

void Graph::insertEdge(Vertex& v1, Vertex& v2){
    if (!(v1 == v2)) {
        Edge* newEdge  = new Edge(edgeNum, v1.node_id_, v2.node_id_);
        edgeNum++;
        AdjList->at(&v1)->push_back(*newEdge);
        v1.degree_++;
        EdgeList->push_back(*newEdge);
        // AdjList->at(&v2)->push_back(*newEdge);
        // v2.degree_++;
    }
};

void Graph::removeEdge(Vertex& v1, Vertex& v2){

};


std::list<Edge>* Graph::incidentEdges(Vertex& v){
    return AdjList->at(&v);
};

void Graph::displayGraph(){
    for(auto i : *AdjList){
        size_t vId = i.first->node_id_;
        std::cout<<vId<<" : ";
        std::list<Edge> currList = *(i.second);
        for(auto currEdge : currList){
            std::cout<< currEdge.initial_node_id_ << "=>"  << currEdge.terminal_node_id_ <<" ";
        }
        std::cout<<std::endl;
    }
};
