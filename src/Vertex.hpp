/*
 * Vertex.h
 *
 *  Created on: Jan 27, 2016
 *      Author: kevinchan
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include "Edge.hpp"
#include <vector>

//Health status enumeration definition
enum HealthStatus { SUSCEPTABLE, EXPOSED, INFECTIOUS, VACCINATED, DECEASED, RECOVERED };


//Vertex class definition
class Vertex {
public:
    //static methods
    static int getNumVertices(){ return Vertex::numVertices; }
    
	//constructors and destructors
	Vertex();
    Vertex(int id);
	virtual ~Vertex();

	//public methods
	void addEdge(Vertex* neighbour, double weight); //allocate edge and add to vector of edges
	int getDegree(); //return number of connected edges
	void deleteEdges(); //delete and deallocate all edges
    void deleteOwnEdges(); //delete and deallocate my edges only i.e. does not delete neighbour's edges
    void deleteEdges(Vertex* neighbour); //delete and allocate matching edges for neighbour
    bool isNeighbour(Vertex* vertex); //check if given vertex is a neighbour
    void incrementDaysSinceExposed();
    void incrementDaysSinceInfectious();
    double clusteringCoefficient(); //calculate clustering Coefficent for a undirected graph
    
	//getters and setters
	std::vector<Edge*>& getEdges() {
		return this->edges;
	}

	void setEdges(const std::vector<Edge*>& edges) {
		this->edges = edges;
	}

    HealthStatus getHealthStatus() {
        return this->healthStatus;
    }
    
    void setHealthStatus(HealthStatus healthStatus) {
        this->healthStatus = healthStatus;
    }
    
    int getDaysSinceExposed() {
        return this->daysSinceExposed;
    }
    
    void setDaysSinceExposed(int daysSinceExposed) {
        this->daysSinceExposed = daysSinceExposed;
    }
    
    int getDaysSinceInfectious() {
        return this->daysSinceInfectious;
    }
    
    void setDaysSinceInfectious(int daysSinceInfectious) {
        this->daysSinceInfectious = daysSinceInfectious;
    }
    
    int getRecoveryTime() {
        return this->recoveryTime;
    }
    
    void setRecoveryTime(int recoveryTime) {
        this->recoveryTime = recoveryTime;
    }
    
    bool getIsVaccineAdopter() {
        return this->isVaccineAdopter;
    }
    
    void setIsVaccineAdpoter(bool isVaccineAdopter) {
        this->isVaccineAdopter = isVaccineAdopter;
    }
    
    double getAdoptionThreshold() {
        return this->adoptionThreshold;
    }
    
    void setAdoptionThreshold(double adoptionThreshold) {
        this->adoptionThreshold = adoptionThreshold;
    }
    
    int getId() {
        return id;
    }
    
    void setId(int id) {
        this->id = id;
    }
    
    int getAgeGroup() {
        return this->ageGroup;
    }
    
    void setAgeGroup(int ageGroup) {
        this->ageGroup = ageGroup;
    }
    
    int getAge(){
        return this->age;
    }
    
    void setAge(int age){
        this->age = age;
    }
    
private:
    //private members
	static int numVertices;
	std::vector<Edge*> edges;
    HealthStatus healthStatus;
    int daysSinceExposed;
    int daysSinceInfectious;
    int recoveryTime;
    bool isVaccineAdopter;
    int adoptionThreshold;
    int id;
    int ageGroup;
    int age;
    
    //private methods
    void init();
};

#endif /* VERTEX_H_ */
