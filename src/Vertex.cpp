/*
 * Vertex.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: kevinchan
 */

#include "Vertex.hpp"

int Vertex::numVertices = 0;

Vertex::Vertex() {
	++Vertex::numVertices;
    init();
}

Vertex::Vertex(int id) {
    ++Vertex::numVertices;
    this->id = id;
    init();
}

Vertex::~Vertex() {
	//remove edges
	deleteEdges();
	--Vertex::numVertices;
}

void Vertex::init() {
    this->healthStatus = SUSCEPTABLE;
    this->daysSinceExposed = 0;
    this->daysSinceInfectious = 0;
    this->recoveryTime = 0;
    this->isVaccineAdopter = false;
    this->adoptionThreshold = 0;
    this->ageGroup = 0;
    this->age = 0;
}


int Vertex::getDegree() {
	return (int)this->edges.size();
}

void Vertex::addEdge(Vertex* neighbour, double weight) {
    //create new edge
    Edge* edge = new Edge(neighbour, weight);
    this->edges.push_back(edge);
}

void Vertex::deleteEdges() {
	//remove edge from neighbours edges
    for (std::vector<Edge*>::iterator edge = this->edges.begin(); edge != this->edges.end(); ++edge) {
        
		//delete neighbours edges
		Vertex* neighbour = (*edge)->getNeighbour();
        neighbour->deleteEdges(this);
        
        //deallocate edge
        delete (*edge);
	}
	//clear edge map
	this->edges.clear();
}

void Vertex::deleteEdges(Vertex* neighbour) {
    //remove edges for neighbour
    for (std::vector<Edge*>::iterator iter = this->edges.begin(); iter != this->edges.end(); /*increment only if no deletion made*/) {
        
        Edge* edge = *iter;
        if (edge->getNeighbour()==neighbour) { //match found
            this->edges.erase(iter); //remove from vector
            delete edge; //deallocate edge
        } else {
            ++iter;
        }
    }
}

void Vertex::deleteOwnEdges() {
    //deallocate edges
    for (std::vector<Edge*>::iterator edge = this->edges.begin(); edge != this->edges.end(); ++edge) {
        //deallocate edge
        delete (*edge);
    }
    //clear edge vector
    this->edges.clear();
}


bool Vertex::isNeighbour(Vertex* vertex) {
    //find neighbour
    for (std::vector<Edge*>::iterator edge = this->edges.begin(); edge != this->edges.end(); ++edge) {
        //get edge vertex
        Vertex* neighbour = (*edge)->getNeighbour();
        if (neighbour==vertex) {
            return true;
        }
    }
    return false;
}

double Vertex::clusteringCoefficient() {
    
    double clusteringCoef;

    //calculate strength = sum of weights
    //calculate degree
    //calculate sum of weights, for all combination of neighbours that are connected
    //clustering coefficient = (sum of weights of shared neighbours)/(2*strength*(degree-1))
    
    double strength = 0;
    double triangleWeights = 0;
    int degree = (int)this->edges.size();
    
    //iterate across edges
    for (std::vector<Edge*>::iterator edge = this->edges.begin(); edge != this->edges.end(); ++edge){
        
        //iterate across neighbours' neighbours
        Vertex* neighbour = (*edge)->getNeighbour();
        std::vector<Edge*> neighboursEdges = neighbour->getEdges();
        for (std::vector<Edge*>::iterator neighboursEdge = neighboursEdges.begin(); neighboursEdge != neighboursEdges.end(); ++neighboursEdge) {
            //check if neighbour is vertex's neighbour
            if ((*neighboursEdge)->getNeighbour()->isNeighbour(this)) {
                //increment cliqueWeights
                triangleWeights += (*edge)->getWeight();
            }
        }
        //increment strength
        strength += (*edge)->getWeight();
    }
    
    //calculate coef
    clusteringCoef = triangleWeights/(strength*(degree-1));
    
    return clusteringCoef;
}

void Vertex::incrementDaysSinceExposed() {
    this->daysSinceExposed++;
}

void Vertex::incrementDaysSinceInfectious() {
    this->daysSinceInfectious++;
}
