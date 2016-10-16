/*
 * Graph.h
 *
 *  Created on: Jan 27, 2016
 *      Author: kevinchan
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Vertex.hpp"
#include <vector>

//A Graph object is a container for pointers to vertices (with self-contained edges)
class Graph {
public:
    //static methods
    static void completeGraph(std::vector<Vertex*> &vertices);
    static void randomGraph(std::vector<Vertex*> &vertices, int degree);
    static void wattsStrogatzGraph(std::vector<Vertex*> &vertices, int meanDegree, double rewiringProb);
    static void ringLatticeGraph(std::vector<Vertex*> &vertices, int degree);
    static void addUndirectedEdge(Vertex* v1, Vertex* v2, double weight);
    static void removeUndirectedEdge(Vertex* v1, Vertex* v2);
    static void removeDirectedEdge(Vertex* fromVertex, Vertex* toVertex); //remove and deallocate edge
    static void rewireEdges(std::vector<Vertex*> &vertices, double rewiringProb);
    
	//constructer and destructor
	Graph(); //construct empty graph
	Graph(int numVertices); //construct graph with numVertices allocated and initialized
	virtual ~Graph(); //destruct graph and deallocate vertices

	//public methods
	void addVertex(); //allocate and add a new empty vertex, returning vertex pointer
	void addVertex(Vertex* vertex); //add a vertex pointer
	void addVertices(int numVertices); //allocate and add multiple vertices
	void removeVertex(Vertex* vertex); //remove vertex pointer from graph, deallocate memory and remove associated edges
	void removeAllVertices(); //remove and deallocate all vertices
	void addDirectedEdge(Vertex* fromVertex, Vertex* toVertex, double weight); //allocate and add edge between two given vertices with given weight
    void printEdges(); //print edges of the graph
    double clusteringCoefficient(); //get global clustering coefficient of graph
    std::vector<double> shortestPath(Vertex *vertex); //returns a copy to a vector of shortest path distances
    double avgPathLength(); //returns the average path lengtb of the graph
    double avgPathLenghtNonVaccinators(); //returns the average path length of non-vaccianting sub-graph
    
	//getters and setters
	int getNumVertices() {
		return (int)this->vertices.size();
	}

    std::vector<Vertex*>& getVertices() {
		return vertices;
	}

	void setVertices(const std::vector<Vertex*>& vertices) {
		this->vertices = vertices;
	}

protected:
	//private members
	std::vector<Vertex*> vertices;
};

#endif /* GRAPH_H_ */
