#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

#include <iostream>
#include <unordered_map>
#include <list> 

Graph::Graph(){
    edgeNum_ = 0;
};

void Graph::insertVertex(Vertex& v){
    std::list<EdgeListIterator> newList;
    adjList_.insert(std::make_pair(v.hash(), newList));
    vertexMap_.insert(std::make_pair(v.hash(), v));
};

void Graph::removeVertex(Vertex& v){
        
};

bool Graph::areAdjacent(Vertex& v1, Vertex& v2){

};

void Graph::insertEdge(Vertex& v1, Vertex& v2){
    if (!(v1.hash() == v2.hash())) {
        Edge newEdge = Edge(edgeNum_, v1.hash(), v2.hash());
        // Push to the front
        edgeList_.push_front(newEdge); 
        // Return what was just inserted to the front of the edgeList_
        adjList_.at(v1.hash()).push_front(edgeList_.begin());  // if rbegin() worked, I would've kept it at push_back for edgeList_
        v1.degree_++;
        adjList_.at(v1.hash()).back()->edgeInSrcVertex = adjList_.at(v1.hash()).begin();
        // adjList_->at(&v2)->push_back(*newEdge);
        // v2.degree_++;
    }
};

void Graph::removeEdge(Vertex& v1, Vertex& v2){

};

std::list<EdgeListIterator>& Graph::incidentEdges(Vertex& v){
    return adjList_.at(v.hash());
};

void Graph::displayGraph(){
    for(auto i : adjList_){
        size_t vId = i.first;
        std::cout<<vId<<" : ";
        for(auto currEdge : i.second){
            std::cout<< currEdge->initial_node_id_ << "=>"  << currEdge->terminal_node_id_ << " ";
        }
        std::cout<<std::endl;
    }
};
