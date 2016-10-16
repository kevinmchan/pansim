/*
 * Graph.cpp
 *
 *  Created on: Jan 27, 2016
 *      Author: kevinchan
 */

#include "Graph.hpp"
#include <iostream>
#include <random>
#include <set>
#include "MinHeap.h"

void Graph::wattsStrogatzGraph(std::vector<Vertex*> &vertices, int meanDegree, double rewiringProb) {
    
    int numVertices = (int)vertices.size();
    
    //check that vertices is not empty
    if (vertices.size()==0) {
        std::cout << "Warning: vertices is an empty vector" << std::endl;
        return;
    }
    
    //check that degree is smaller than numVertices
    if (meanDegree >= numVertices) {
        std::cout << "Warning: degree must be smaller than number of vertices" << std::endl;
        std::cout << "Setting degree to one less than number of vertices" << std::endl;
        meanDegree = (int)numVertices - 1;
    }
    
    //generate ring lattice
    ringLatticeGraph(vertices, meanDegree);
    
    //rewire graph edges
    rewireEdges(vertices, rewiringProb);
    
    }

void Graph::rewireEdges(std::vector<Vertex*> &vertices, double rewiringProb) {
    
    int numVertices = (int)vertices.size();
    
    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd;
    // Use Mersenne twister engine to generate pseudo-random numbers.
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> realDist(0.0, 1.0);
    std::uniform_int_distribution<int> intDist(0,numVertices-2); //subtract by two because of zero indexing and not selecting oneself
    
    //rewire edges with rewiringProb
    //iterate across vertices
    for (int vertexIndex = 0; vertexIndex < numVertices; ++vertexIndex) {
        
        Vertex* currentVertex = vertices[vertexIndex];
        
        //iterate across edges
        std::vector<Edge*> edges = currentVertex->getEdges();
        
        for (std::vector<Edge*>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
            //rewire with rewiring Prob
            if (rewiringProb >= realDist(engine)) {
                
                bool connectedAlready = false;
                Vertex* originalNeighbour = (*edge)->getNeighbour();
                
                do{
                    //select edge to rewire to
                    int targetIndex = intDist(engine);
                    
                    //check if neighbour drawn is above vertIndex
                    if (targetIndex >= vertexIndex) {
                        targetIndex++; //pad index to prevent drawing self
                    }
                    Vertex* targetVertex = vertices[targetIndex];
                    
                    connectedAlready = currentVertex->isNeighbour(targetVertex);
                    if (!connectedAlready) {
                        //swap vertices
                        (*edge)->setNeighbour(targetVertex);
                        targetVertex->addEdge(currentVertex, (*edge)->getWeight());
                        originalNeighbour->deleteEdges(currentVertex);
                    }
                } while (connectedAlready);
            }
        }
    }
}

void Graph::ringLatticeGraph(std::vector<Vertex*> &vertices, int degree) {
    
    size_t numVertices = vertices.size();
    
    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd;
    // Use Mersenne twister engine to generate pseudo-random numbers.
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    
    //iterate across each vertex and add edge to degree/2 neighbours on both sides
    for (int index = 0; index < numVertices; index++) {
        //iterate across degree/2 neighbours to the right
        //because edges are undirected, no need to add edges to the left
        for (int shift = 1; shift <= degree/2; shift++) {
            //get neighbour index
            int neighbourIndex = (index+shift)%(numVertices); //take mod to wrap index for edge cases
            
            //connect vertices
            addUndirectedEdge(vertices[neighbourIndex], vertices[index], dist(engine));
        }
    }
}


void Graph::completeGraph(std::vector<Vertex*> &vertices) {
    
    //connect all edges
    for (std::vector<Vertex*>::iterator it1 = vertices.begin(); it1!=vertices.end(); ++it1) {
        // Use random_device to generate a seed for Mersenne twister engine.
        std::random_device rd;
        // Use Mersenne twister engine to generate pseudo-random numbers.
        std::mt19937 engine(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        
        // Connect all edges
        for (std::vector<Vertex*>::iterator it2 = vertices.begin(); it2<it1; ++it2) {
            addUndirectedEdge(*it1, *it2, dist(engine));
        }
    }
}

void Graph::randomGraph(std::vector<Vertex*> &vertices, int meanDegree) {
    
    int numVertices = (int)vertices.size();
    
    // Check for non-empty set of vertices
    if (numVertices<=0) {
        return;
    }
    
    // Check that degree is less than number of vertices
    if (numVertices < meanDegree) {
        // lower degree to numVertices
        meanDegree = numVertices;
    } else if(numVertices == meanDegree) {
        meanDegree--;
    }
    
    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd;
    // Use Mersenne twister engine to generate pseudo-random numbers.
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> realDist(0.0, 1.0);
    std::uniform_int_distribution<int> intDist(0, numVertices-2); //subtract by 2 to account for zero indexing and drawing self
    
    //connect vertices to <meanDegree/2> random neighbours
    for (int vertIndex = 0; vertIndex < numVertices; vertIndex++) {
        
        //connect vertices to <meanDegree/2> random neighbours
        for (int neighbourCount = 0; neighbourCount < meanDegree/2; neighbourCount++) {
            //draw neighbour until new neighbour found
            bool alreadyNeighbour;
            int neighbour;
            do{
                //generate neighbour index
                neighbour = intDist(engine);
                
                //check if neighbour drawn is above vertIndex
                if (neighbour >= vertIndex) {
                    neighbour++; //pad index to prevent drawing self
                }
                
                //add shuffled vertex if not already neighbour
                alreadyNeighbour = vertices[vertIndex]->isNeighbour(vertices[neighbour]);
                if (!alreadyNeighbour) {
                    //add edges
                    addUndirectedEdge(vertices[vertIndex], vertices[neighbour], realDist(engine));
                }
            } while (alreadyNeighbour);
        }
    }
}

Graph::Graph() {}

Graph::Graph(int numVertices) {
	addVertices(numVertices);
}

Graph::~Graph() {
	removeAllVertices();
}

void Graph::addVertex() {
	Vertex* vertex = new Vertex(this->getNumVertices());
	addVertex(vertex);
}

void Graph::addVertex(Vertex* vertex) {
	this->vertices.push_back(vertex);
}

void Graph::addVertices(int numVertices) {
	for(int i = 0; i < numVertices; i++) {
        addVertex();
	}
}

void Graph::removeVertex(Vertex* vertex) {
	//get position of vertex
	std::vector<Vertex*>::iterator position = std::find(this->vertices.begin(), this->vertices.end(), vertex);

	//remove vertex in position found
	if (position != this->vertices.end()) { // == vertices.end() means the element was not found
		
        //get id of vertex being replaced in order to preserve labelling of vertices {0..numVertices-1}
        int id = vertex->getId();
        
        //swap vertex being removed with back vertex (and swap vertex id)
        this->vertices.back()->setId(id);
        (*position) = vertices.back();
        
        //pop back vertex
        this->vertices.pop_back();
        
		//deallocate vertex memory
		delete vertex;

	} else {
		std::cout << "WARNING: Vertex to be removed was not found!" << std::endl;
	}

}

void Graph::removeAllVertices() {
	//deallocate vertices
	for(std::vector<Vertex*>::iterator it = this->vertices.begin(); it!=this->vertices.end(); ++it) {
        Vertex* vertex = *it;
        vertex->deleteOwnEdges();
		delete vertex;
	}
	//clear vertices vector
	this->vertices.clear();
}

void Graph::addDirectedEdge(Vertex* fromVertex, Vertex* toVertex, double weight) {
	fromVertex->addEdge(toVertex, weight);
}

void Graph::addUndirectedEdge(Vertex* v1, Vertex* v2, double weight) {
	v1->addEdge(v2, weight);
	v2->addEdge(v1, weight);
}

void Graph::removeDirectedEdge(Vertex* fromVertex, Vertex* toVertex) {
	fromVertex->deleteEdges(toVertex);
}

void Graph::removeUndirectedEdge(Vertex* v1, Vertex* v2) {
	v1->deleteEdges(v2);
	v2->deleteEdges(v1);
}

void Graph::printEdges() {
    
    std::cout << "Printing all graph edges:" << std::endl;
    
    //iterate over all vertices
    for (std::vector<Vertex*>::iterator vertex = this->vertices.begin(); vertex != this->vertices.end(); ++vertex) {
        //iterate over all edges
        for (std::vector<Edge*>::iterator edge = (*vertex)->getEdges().begin(); edge != (*vertex)->getEdges().end(); ++edge) {
            std::cout << (*vertex)->getId() << "\t" << (*edge)->getNeighbour()->getId() << "\t" << (*edge)->getWeight() << std::endl;
        }
    }
    
}

double Graph::avgPathLength() {
    
    std::cout << "Calculating average path" << std::endl;
    
    double sumPathLength = 0;
    int numEdges = 0;
    
    //sum path lengths across all vertices
    for (int i = 0; i < getNumVertices(); i++) {
        std::cout << "Calculating path length for vertex " << i << std::endl;
        std::vector<double> pathLengths = shortestPath(this->vertices[i]);
        
        //sum all path length for vertex i
        for (int j = 0; j < pathLengths.size(); j++) {
            //on't include path to self; only sum if not infinity
            if (i != j && pathLengths[j] != std::numeric_limits<double>::max()) {
                numEdges++;
                sumPathLength += pathLengths[j];
            }
        }
    }
    
    return sumPathLength/numEdges;
}

double Graph::clusteringCoefficient() {
    
    //calculate global clustering coefficient
    std::cout << "Calculating clustering coef" << std::endl;
    
    double clusteringCoef = 0;
    int numVertices = 0;
    
    for (std::vector<Vertex*>::iterator vertex = this->vertices.begin(); vertex != this->vertices.end(); ++vertex) {
        double localClusteringCoef = (*vertex)->clusteringCoefficient();
        if (!isnan(localClusteringCoef)) {
            clusteringCoef += localClusteringCoef;
            numVertices++;
        }
    }
    clusteringCoef /= numVertices;
    
    return clusteringCoef;
}

//Implementation of dijkstra's algorithm to find shortest path, using min heaps
std::vector<double> Graph::shortestPath(Vertex *source) {
    int V = this->getNumVertices(); // Get the number of vertices in graph
    int src = source->getId();
    std::vector<double> dist(V,std::numeric_limits<double>::max()); // dist values used to pick minimum weight edge in cut
    
    // minHeap represents set E
    struct MinHeap* minHeap = new MinHeap(V);
    
    // Initialize min heap with all vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        minHeap->array[v]->dist = dist[v];
        minHeap->array[v]->v = v;
        minHeap->pos[v] = v;
    }
    
    // Make dist value of src vertex as 0 so that it is extracted first
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    
    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
        
        // Get u's neighbours
        std::vector<Edge*> neighbourEdges = this->vertices[u]->getEdges();
        
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        for (int i = 0; i < neighbourEdges.size(); i++) {
            int v = neighbourEdges[i]->getNeighbour()->getId();
            
            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != std::numeric_limits<double>::max() && neighbourEdges[i]->getWeight() + dist[u] < dist[v]) {
                dist[v] = dist[u] + neighbourEdges[i]->getWeight();
                
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
        }
    }
    
    delete minHeap;
    
    return dist;
}

/* Old implementation of shortestPath finder (dijkstra's algorithm); abandoned due to speed
std::vector<double> Graph::shortestPath(Vertex* source) {
    
    // vector to store min distances
    std::vector<double> distances = std::vector<double>(this->getNumVertices(), std::numeric_limits<double>::max());
    distances[source->getId()] = 0;
    
    //create an ordered set to store all active pairs of vertices and their distances
    std::set<std::pair<double, Vertex*>> activeVertices;
    activeVertices.insert({0,source});
    
    //while active set is not empty
    while (!activeVertices.empty()) {
        Vertex* current = activeVertices.begin()->second;
        activeVertices.erase(activeVertices.begin());
        for (std::vector<Edge*>::iterator edge = current->getEdges().begin(); edge != current->getEdges().end(); ++edge) {
            Vertex* neighbour = (*edge)->getNeighbour();
            if (distances[neighbour->getId()] > distances[current->getId()] + (*edge)->getWeight()) {
                activeVertices.erase({distances[neighbour->getId()], neighbour});
                distances[neighbour->getId()] = distances[current->getId()] + (*edge)->getWeight();
                activeVertices.insert({distances[neighbour->getId()], neighbour});
            }
        }
    }
    
    return distances;
}
*/