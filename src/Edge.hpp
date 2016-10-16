/*
 * Edge.h
 *
 *  Created on: Jan 27, 2016
 *      Author: kevinchan
 */

#ifndef EDGE_H_
#define EDGE_H_

//Enumeration definition
enum ConnectionType { WORK, SCHOOL, TRANSIT, COMMUNITY, PATIENT, HOME };

//declarations
class Vertex;

//Edge class definition:
class Edge {
public:
    //static methods
    static int getNumEdges(){ return Edge::numEdges; }
    
	//constructors and destructors
	Edge(); //construct empty edge
	Edge(Vertex* neighbour, double weight); //construct edge with given neighbour and weight
    Edge(Vertex* neighbour, double weight, ConnectionType type); //construct edge with given neighbour, weight and type
	virtual ~Edge(); //destruct edge

	//getters and setters
	Vertex* getNeighbour() {
		return neighbour;
	}

	void setNeighbour(Vertex* neighbour) {
		this->neighbour = neighbour;
	}

	double getWeight() {
		return weight;
	}

	void setWeight(double weight) {
		this->weight = weight;
	}
    
    ConnectionType getConnectionType() {
        return type;
    }
    
    void setConnectionType(ConnectionType type) {
        this->type = type;
    }

private:
	//private members
	static int numEdges;
	Vertex* neighbour;
	double weight;
    ConnectionType type;
};

#endif /* EDGE_H_ */
