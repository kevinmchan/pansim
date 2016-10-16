/*
 * Edge.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: kevinchan
 */

#include "Edge.hpp"
#include <iostream>

int Edge::numEdges = 0;

Edge::Edge() {
	this->neighbour = nullptr;
	this->weight = 0;
    ++Edge::numEdges;
    this->type = WORK;
}

Edge::Edge(Vertex* neighbour, double weight) {
	this->neighbour = neighbour;
	this->weight = weight;
    ++Edge::numEdges;
    this->type = WORK;
}

Edge::Edge(Vertex* neighbour, double weight, ConnectionType type) {
    this->neighbour = neighbour;
    this->weight = weight;
    ++Edge::numEdges;
    this->type = type;
}

Edge::~Edge() {
    --Edge::numEdges;
}
